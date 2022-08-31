#ifndef STRUCT_H
# define STRUCT_H

# define HEIGTH_WINDOW 1020
# define WIDTH_WINDOW 1720

typedef struct s_vector
{
	double	x;
	double	y;
}			t_vector;

typedef struct	s_data_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_data_img	*img;
}				t_data;


#endif