#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "struct.h"
# include "libft.h"

#define mapWidth 24 
#define mapHeight 24 

//tools
void		my_mlx_pixel_put(t_data_img	*data, int	x, int	y, int	color);
int			create_trgb(int	t, int	r, int	g, int	b);
int			close_window(t_data *data);
int			ft_error(int fd, char *error, int ret);
//parser
int			parser(int argc, char *argv[], t_data *data);
//checker
int			save_map(char *map, int i, t_data *data);
int			save_color(char *map, int i, t_data *data, char f_or_c);
//	init
void        init_img(t_data *data, t_data_img **img, int width, int higth);
void        init_data(t_data *data);
t_vector	*init_vector(double x, double y);
void	    init_player(t_player *play);
// raycasting
int	    	raycast_loop(t_data	*data);
int     	mouse_action(int x, int y, void *param);
int	    	render(void *param);

#endif