/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arman <arman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:42:34 by arman             #+#    #+#             */
/*   Updated: 2022/10/22 06:42:34 by arman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_data_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_data *data)
{
	free(data->bg);
	free(data->map.img);
	free(data->texture[0]);
	free(data->texture[1]);
	free(data->texture[2]);
	free(data->texture[3]);
	free(data->texture);
	free(data->ray);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

double	to_radiants(double degrees)
{
	return (degrees * M_PI / -180.0);
}

double	to_degrees(double radiants)
{
	return (radiants * 180.0 / M_PI);
}
