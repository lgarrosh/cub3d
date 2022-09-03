/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:22 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/02 13:58:02 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <sys/time.h>
# include <limits.h>
# include "mlx.h"
# include "struct.h"
# include "libft.h"

#define mapWidth 24 
#define mapHeight 24 

//tools
void			my_mlx_pixel_put(t_data_img *data, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);
int				close_window(t_data *data);
int				ft_error(int fd, char *error, int ret);
int				find_time(void);
void			ft_sleep(int time);
void			cufoff_frime(int *time, int fps);
//parser
int			    parser(int argc, char *argv[], t_data *data);
//checker
int			    save_map(char *map, int i, t_data *data);
int			    save_color(char *map, int i, t_data *data, char f_or_c);
//	init
void	        init_img(t_data *data, t_data_img **img, int width, int heigth);
void			init_data(t_data *data);
t_vector		*init_vector(double x, double y);
void			init_player(t_player *play);
// raycasting
int				raycast_loop(t_data	*data);
int				mouse_action(int x, int y, void *param);
int				render(void *param);
void			line_dda(t_data *data, double x1, double y1, double x2, double y2);
void			put_cell(t_data *data);

#endif