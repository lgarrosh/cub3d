#ifndef STRUCT_H
# define STRUCT_H

# define HEIGTH_WINDOW 1020
# define WIDTH_WINDOW 1720


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
}				t_data_img;

typedef struct s_struct
{
	int color;
	int mouse_x;
	int mouse_y;
} 				t_struct;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_struct	other;
	t_data_img	*img;
	t_player	play;
	int			fps;
}				t_data;

#endif