#ifndef STRUCT_H
#define STRUCT_H

#include "libft.h"

#define HEIGTH_WINDOW 704
#define WIDTH_WINDOW 1000

#define MAP_TILE_SIZE 30

#define	NEGATIVE_y 1
#define	NEGATIVE_X 3
#define SPEED 2

#define W_KEY 13
#define D_KEY 2
#define S_KEY 1
#define A_KEY 0

typedef struct s_vector
{
	double x;
	double y;
} t_vector;

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

typedef struct s_ray
{
	t_vector	x_end; // координаты пересечения
	t_vector	move_cor; // длина перемещения по x при движении в y на 1 еденицу (и наоборот)
	t_vector	delta; // длина до первого пересечения по x и y
	double		ray; // длина
	double		rad; // угол
	int			step; 
} t_ray;

typedef struct s_player
{
	t_vector	pos; // координаты игрока
	t_vector	map; // координаты клетки на карте в которой находиться игрок
	t_vector	dir; // вектор напровления
	t_vector	off; // отступ внутри клетки
	double		rad; // угол напровления в радианах
	double		grad; // угол напровления в градусах
} t_player;

typedef struct s_minimap
{
	char **map;		   // карта
	int bitmap_width;  // ширина карты
	int bitmap_height; // высота карты
	t_data_img *img;   // мини-карта
} t_minimap;

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
	double		rad_del; // угол между лучам радианах
	double		grad_del; // угол между лучам градусах
	double		review; // обзор
	int			flag; // напровление луча
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