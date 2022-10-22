/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arman <arman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 05:54:51 by arman             #+#    #+#             */
/*   Updated: 2022/10/22 05:54:51 by arman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <float.h>
# include <math.h>
# include "mlx.h"
# include "struct.h"
# include "libft.h"

void		my_mlx_pixel_put(t_data_img	*data, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);
int			close_window(t_data *data);
int			ft_error(int fd, char *error, int ret);
double		to_radiants(double degrees);
double		to_degrees(double radiants);
double		ft_cos(double rad);
double		ft_sin(double rad);
t_vector	sum_vector(t_vector v1, t_vector v2);
void		ft_skybox(int x, t_data *data);
void		load_img(t_data_img *img, int **texture);
void		move(t_data *data);
int			parser(int argc, char *argv[], t_data *data);
int			save_map(char *map, int i, t_data *data);
int			save_color(char *line, t_data *data, char dir);
int			string_to_rgb(char *rgb_s);
void		init_img(t_data *data, t_data_img **img, int width, int higth);
void		init_data(t_data *data);
t_vector	init_vector(double x, double y);
int			raycast_loop(t_data	*data);
void		mouse_action(t_data	*data);
int			render(void *param);
void		draw_map_grid(t_data *data);
void		calculate_delta(t_data *data, t_ray *ray);
void		calculate_ray(t_data *data, t_ray *ray);
void		ft_ravno(int *x, int *y, int i, int j);
void		mini_map(t_data *data, char **map);
void		line_dda(t_data_img *data, t_vector a, t_vector b);
void		calculate_3d(t_data *data, t_ray *ray, int x);
void		calculate_ray(t_data *data, t_ray *ray);
void		raycasting(t_data *data);
void		floor_ceiling(t_data *data);
void		draw_everything(t_data *data);
void		uslov(t_data *data, char ch, int i, int j);
void		find_bitmap_dimensions(char *map, t_data *data);
void		string_to_array_of_strings(char *map, t_data *data);
void		empty_to_dash(t_data *data);
void		find_player_cooridnates(t_data *data);
int			check_map(char *string, t_data *data);
void		ft_free_info(char **info);
int			check_and_save_data(char **info, t_data *data);
int			check_map_t(t_data *data, char *string, int i);
int			check_map(char *string, t_data *data);
void		ft_rad(t_data *data, char ch);

#endif