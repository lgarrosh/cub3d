#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "struct.h"
# include "libft.h"

//tools
void		my_mlx_pixel_put(t_data	*data, int	x, int	y, int	color);
int			create_trgb(int	t, int	r, int	g, int	b);
int			close_window(void *param);
void 		*error(int fd, char *error, int _return);
//	init
t_data		*init_img(t_vars *var, int width, int higth);
t_vector    *init_vector(float x, float y);
t_vars		*init_winow(int width, int higth);

#endif