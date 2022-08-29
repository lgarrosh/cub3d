#ifndef STRUCT_H
# define STRUCT_H

# define HIGTH_WINDOW 1020
# define WIDTH_WINDOW 1720

typedef struct s_vector
{
	float			x;
	float			y;
}			t_vector;

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

#endif