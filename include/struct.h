#ifndef STRUCT_H
# define STRUCT_H

#include "libft.h"

# define HEIGTH_WINDOW 1020
 # define WIDTH_WINDOW 1720

# define MAP_TILE_SIZE 30

# define W_KEY 13
# define D_KEY 2
# define S_KEY 1
# define A_KEY 0


typedef struct	s_vector
{
	double	x;
	double	y;
}			t_vector;

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}			t_player;

typedef struct	s_data_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data_img;

typedef struct s_sprite
{
	void	*img;
	int		width;
	int		height;
	char	*path;
} 				t_sprite;

typedef struct s_struct
{
	int			f_color; // цвет пола
	int			c_color; // цвет потолка
	char		**map; // карта
	int			bitmap_width; // ширина карты
	int			bitmap_height; // высота карты
	int			mouse_x; // координаты мышки 
	int			mouse_y; // координаты мышки 
} 				t_struct;

typedef struct s_minimap
{
	t_vector	player; // координаты на всей карте
	int			x_bitmap; // координаты клетки по x
	int			y_bitmap; // координаты клетки по y
	int			x_off; // отступ внутри клетки (положения игрока)
	int			y_off; // отступ внутри клетки (положения игрока)
	t_data_img	*img; // мини-карта
} 				t_minimap;

typedef struct	s_ray
{
	double		x_end; // координаты пересечения 
	double		y_end; // координаты пересечения
	double		ray; // длина 
	double		rad; // угол 
	char		type; // восток запод 
}			t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_struct	other;
	t_data_img	*bg;
	t_minimap	minimap;
	t_player	play;
	int			fps;
	t_sprite	skybox; // небо
	int			sky_offset; // смещение небо по x
	double		rad; // угол в ра
	t_ray		rays[WIDTH_WINDOW]; // лучи
}				t_data;

#endif