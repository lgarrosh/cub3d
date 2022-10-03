#ifndef STRUCT_H
#define STRUCT_H

#include "libft.h"

#define HEIGTH_WINDOW 704
#define WIDTH_WINDOW 1000

#define MAP_TILE_SIZE 30

#define W_KEY 13
#define D_KEY 2
#define S_KEY 1
#define A_KEY 0

typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_pos
{
	int x;
	int y;
}			t_pos;

typedef struct s_data_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_data_img;

typedef struct s_sprite
{
	void *img;
	int width;
	int height;
	char *path;
} t_sprite;

typedef struct s_player
{
	t_vector	pos; // координаты игрока
	t_pos		map; // координаты клетки на карте в которой находиться игрок
	t_vector	dir; // вектор напровления
	t_vector	off; // отступ внутри клетки
} t_player;

typedef struct s_minimap
{
	char **map;		   // карта
	int bitmap_width;  // ширина карты
	int bitmap_height; // высота карты
	t_data_img *img;   // мини-карта
} t_minimap;

typedef struct s_ray
{
	t_vector x_end; // координаты пересечения со стеной
	double ray;		// длина
	double rad;		// угол
	char type;		// восток запод
} t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			f_color; // цвет пола
	int			c_color; // цвет потолка
	t_minimap	map; // мини-карта
	t_data_img	*bg;
	t_player	play; // игрок
	int			fps;
	t_sprite	skybox; // небо
	int			sky_offset;	// смещение небо по x
	double		rad;
	t_ray		rays[WIDTH_WINDOW]; // лучи
} t_data;

// typedef struct s_minimap
// {
// 	t_vector	player; // координаты на всей карте
// 	int			x_bitmap; // координаты клетки по x
// 	int			y_bitmap; // координаты клетки по y
// 	int			x_off; // отступ внутри клетки (положения игрока)
// 	int			y_off; // отступ внутри клетки (положения игрока)
// 	t_data_img	*img; // мини-карта
// } 				t_minimap;

// typedef struct s_struct
// {
// 	int			f_color; // цвет пола
// 	int			c_color; // цвет потолка
// 	char		**map; // карта
// 	int			bitmap_width; // ширина карты
// 	int			bitmap_height; // высота карты
// 	int			mouse_x; // координаты мышки
// 	int			mouse_y; // координаты мышки
// } 				t_struct;

#endif