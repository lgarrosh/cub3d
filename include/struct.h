/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:26 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/09 11:12:57 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define WIDTH_WINDOW 640
# define HEIGTH_WINDOW 480

# define screenWidth 640
# define screenHeight 480
# define texWidth 64
# define texHeight 64
# define mapWidth 24
# define mapHeight 24

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
}			t_sprite;

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
}			t_struct;

typedef struct s_minimap
{
	t_vector	player;
	t_vector	dir;
	int			x_bitmap;
	int			y_bitmap;
	t_data_img	*img;
}			t_minimap;

typedef struct s_algoritm
{
	unsigned int	buffer[screenHeight][screenWidth];
	unsigned int	textur[8][texHeight * texWidth];
	unsigned int	color;
	t_vector		delta_d; //length of ray from one x or y-side to next x or y-side
	t_vector		ray_dir;
	t_vector		side_d; //length of ray from current position to next x or y-side
	double			move_speed;
	double			frame_time;
	double 			rot_speed;
	double			camera_x;
	double			tex_pos;
	double			perpwd;
	double			wall_x; //where exactly the wall was hit
	double			step;
	int				line_hight;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	int				step_x; //what direction to step in x or y-direction (either +1 or -1)
	int				step_y;
	int				map_x;//which box of the map we're in
	int				map_y;
	int				tex_x;
	int				tex_y;
	int				pitch;
	int				side; //was a NS or a EW wall hit?
	int				hit; //was there a wall hit?
	int				x;
	int				y;
}				t_cub;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_struct	other;
	t_data_img	*bg;
	t_data_img	*raycast;
	t_minimap	minimap;
	t_player	play;
	t_cub		cub;
	int			fps;
	t_sprite	skybox;
	int			sky_offset;
	double		time;
	double		oldtime;
}				t_data;

#endif