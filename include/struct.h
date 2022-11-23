/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 05:58:31 by arman             #+#    #+#             */
/*   Updated: 2022/10/22 21:32:19 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define WIDTH_WINDOW 1020
# define HEIGTH_WINDOW 780
# define SIZE_TEXTURE 64
# define CORNER 66.0
# define MOUSE_SPEED 0.3
# define MAP_TILE_SIZE 20
# define NEGATIVE_Y 1
# define NEGATIVE_X 3
# define SPEED 1.0
# define W_KEY 13
# define D_KEY 2
# define S_KEY 1
# define A_KEY 0

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_vector
{
	double	x;
	double	y;
}		t_vector;

typedef struct s_data_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}		t_data_img;

typedef struct s_sprite
{
	void	*img;
	int		width;
	int		height;
	char	*path;
}		t_sprite;

typedef struct s_ray
{
	t_vector	end;
	t_vector	delta;
	t_vector	ray;
	t_vector	step;
	t_vector	wall;
	double		gipo;
	double		rad;
	double		wall_x;
	int			flag;
	int			flag_direction;
	double		tex_x;
	double		st;
	double		tex_pos;
	double		corner;
	double		perp_dist;
	int			line_height;
}		t_ray;

typedef struct s_player
{
	t_vector	pos;
	t_vector	map;
	t_vector	dir;
	t_vector	off;
	double		rad;
	double		grad;
	int			forward;
	int			back;
	int			left;
	int			right;
	int			turn_l;
	int			turn_r;
}		t_player;

typedef struct s_minimap
{
	char		**map;
	int			bitmap_width;
	int			bitmap_height;
	t_data_img	*img;
}		t_minimap;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			f_color;
	int			c_color;
	t_minimap	map;
	t_data_img	*bg;
	t_data_img	walls[4];
	t_player	play;
	int			fps;
	t_sprite	skybox;
	int			sky_offset;
	double		rad_del;
	double		grad_del;
	double		review;
	int			**texture;
	char		naprav;
	t_ray		*ray;
}		t_data;

#endif