/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:38 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/02 13:58:55 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_img(t_data *data, t_data_img **img, int width, int heigth)
{
	*img = ft_calloc(sizeof(t_data_img), 1);
	if (!img)
	{
		ft_error(2, "error: memory allocation error in function 'init_img'", 1);
		return ;
	}
	(*img)->img = mlx_new_image(data->mlx, width, heigth);
	(*img)->addr = mlx_get_data_addr((*img)->img, &(*img)->bits_per_pixel, &(*img)->line_length, &(*img)->endian);
	(*img)->width = width;
	(*img)->height = heigth;
}

t_vector	*init_vector(double x, double y)
{
	t_vector	*vc;

	vc = malloc(sizeof(t_vector));
	if (!vc)
		return (NULL);
	vc->x = x;
	vc->y = y;
	return (vc);
}

void	init_data(t_data *data)
{
	t_player	play;

	init_player(&play);
	data->other.mouse_x = 0;
	data->other.mouse_y = 0;
	data->play = play;
	data->mlx = mlx_init();
	data->fps = 60;
	data->other.color = 0x00000000;
	data->win = mlx_new_window(data->mlx, WIDTH_WINDOW, HEIGTH_WINDOW, "Spice Boys");
	data->minimap.dir.x = 0;
	data->minimap.dir.y = -50;
	init_img(data, &data->raycast, WIDTH_WINDOW, HEIGTH_WINDOW);
	init_img(data, &data->bg, WIDTH_WINDOW, HEIGTH_WINDOW);
	data->skybox.img = mlx_xpm_file_to_image(data->mlx, "images/skybox.xpm",
		&data->skybox.width, &data->skybox.height);
	init_img(data, &data->minimap.img, MAP_TILE_SIZE * NUMBER_OF_CELLS, MAP_TILE_SIZE * NUMBER_OF_CELLS);
}

void	init_player(t_player *play)
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;

	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	plane.x = 0;
	plane.y = 0;
	play->pos = pos;
	play->dir = dir;
	play->plane = plane;
}
