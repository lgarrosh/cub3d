/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:40:57 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/10/22 21:41:20 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calculate_delta(t_data *data, t_ray *ray)
{
	int	flag_y;
	int	flag_x;

	if (ray->rad > 2 * M_PI)
		ray->rad -= 2 * M_PI;
	flag_y = 7 - NEGATIVE_Y;
	if (ray->rad > 0 && ray->rad < M_PI)
	{
		ray->delta.y = data->play.off.y;
		flag_y = NEGATIVE_Y;
	}
	else
		ray->delta.y = MAP_TILE_SIZE - data->play.off.y;
	flag_x = 7 - NEGATIVE_X;
	if (ray->rad > M_PI / 2 && ray->rad < (3 * M_PI) / 2)
	{
		ray->delta.x = data->play.off.x;
		flag_x = NEGATIVE_X;
	}
	else
		ray->delta.x = MAP_TILE_SIZE - data->play.off.x;
	ray->flag = flag_x & flag_y;
}

int	raycast_loop(t_data	*data)
{
	move(data);
	mouse_action(data);
	floor_ceiling(data);
	mini_map(data, data->map.map);
	raycasting(data);
	draw_everything(data);
	return (0);
}
