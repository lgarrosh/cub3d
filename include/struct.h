/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:26 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/01 21:30:58 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define HEIGTH_WINDOW 700
# define WIDTH_WINDOW 1000

# define MAP_TILE_SIZE 30
# define NUMBER_OF_CELLS 7

# define W_KEY 13
# define D_KEY 2
# define S_KEY 1
# define A_KEY 0

typedef struct s_vector
{
	double	x;
	double	y;
}			t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}			t_player;

typedef struct s_data_img
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
	int			color;
	int			f_color;
	int			c_color;
	char		**map;
	int			bitmap_width;
	int			bitmap_height;
	int			mouse_x;
	int			mouse_y;
} 				t_struct;


typedef struct s_minimap
{
	t_vector	player;
	t_vector	dir;
	int			x_bitmap;
	int			y_bitmap;
	t_data_img	*img;
} 				t_minimap;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_struct	other;
	t_data_img	*bg;
	t_data_img	*raycast;
	t_minimap	minimap;
	t_player	play;
	int			fps;
	t_sprite	skybox;
	int			sky_offset;
}				t_data;

#endif