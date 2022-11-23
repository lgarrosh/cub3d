/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:39:12 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/10/22 21:40:41 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	raycasting(t_data *data)
{
	int	i;

	i = 0;
	while (i < WIDTH_WINDOW)
	{
		data->ray[i].rad = data->play.rad - ((WIDTH_WINDOW / 2) * \
			data->rad_del) + i * data->rad_del;
		calculate_delta(data, &data->ray[i]);
		calculate_ray(data, &data->ray[i]);
		calculate_3d(data, &data->ray[i], i);
		i++;
	}
}

int	intersection_x(t_data *data, t_ray *ray)
{
	int	x;
	int	y;

	ft_ravno(&x, &y, 0, 0);
	if (ray->flag & 6)
		y = (int)data->play.map.y + ray->step.y;
	else if ((int)data->play.map.y)
		y = (int)data->play.map.y - ray->step.y;
	ray->flag_direction = 1;
	if (ray->flag & 3)
		ft_ravno(&x, &ray->flag_direction, \
			(int)data->play.map.x - ray->step.x, 3);
	else if ((int)data->play.map.x)
		x = (int)data->play.map.x + ray->step.x;
	if (data->map.map[y][x] == '1')
	{
		ray->gipo = ray->ray.x;
		ray->end = init_vector(ray->gipo * cos(ray->rad), \
			ray->gipo * -sin(ray->rad));
		ray->wall = init_vector(x, y);
		ray->wall_x = data->play.pos.y + ray->end.y - (y * MAP_TILE_SIZE);
		return (1);
	}
	ray->delta.x += MAP_TILE_SIZE;
	return (0);
}

int	intersection_y(t_data *data, t_ray *ray)
{
	int	x;
	int	y;

	ft_ravno(&x, &y, 0, 0);
	ray->flag_direction = 0;
	if (ray->flag & 6)
		ft_ravno(&y, &ray->flag_direction, \
			(int)data->play.map.y + ray->step.y, 2);
	else if ((int)data->play.map.y)
		y = (int)data->play.map.y - ray->step.y;
	if (ray->flag & 3)
		x = (int)data->play.map.x - ray->step.x;
	else if ((int)data->play.map.x)
		x = (int)data->play.map.x + ray->step.x;
	if (data->map.map[y][x] == '1')
	{
		ray->gipo = ray->ray.y;
		ray->end.x = ray->gipo * cos(ray->rad);
		ray->end.y = ray->gipo * -sin(ray->rad);
		ray->wall = init_vector(x, y);
		ray->wall_x = data->play.pos.x + ray->end.x - (x * MAP_TILE_SIZE);
		return (1);
	}
	ray->delta.y += MAP_TILE_SIZE;
	return (0);
}

int	check_intersection(t_data *data, t_ray	*ray)
{
	if (ray->ray.x < ray->ray.y)
	{
		ray->step.x += 1;
		return (intersection_x(data, ray));
	}
	else
	{
		ray->step.y += 1;
		return (intersection_y(data, ray));
	}
	return (0);
}

void	calculate_ray(t_data *data, t_ray *ray)
{
	ray->step.x = 0;
	ray->step.y = 0;
	while (1)
	{
		ray->ray.x = fabs(ray->delta.x / ft_cos(ray->rad));
		ray->ray.y = fabs(ray->delta.y / ft_sin(ray->rad));
		if (check_intersection(data, ray))
		{
			line_dda(data->map.img, \
			init_vector(data->map.img->width / 2, data->map.img->height / 2), \
			init_vector(data->map.img->width / 2 + ray->end.x, \
			data->map.img->height / 2 + ray->end.y));
			return ;
		}
	}
}
