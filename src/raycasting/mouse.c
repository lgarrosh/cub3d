/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:07 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/08 14:18:54 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	mouse_action(int x, int y, void *param)
{
	t_data		*data;
	static int	x_old;

	if (x >= WIDTH_WINDOW || x < 0)
		return (0);
	if (y >= HEIGTH_WINDOW || y < 0)
		return (0);
	data = (t_data *)param;
	if (x_old < x && x_old != 0)
		data->sky_offset -= (x - x_old) * 2;
	else if (x_old > x && x_old != 0)
		data->sky_offset += (x_old - x) * 2;
	x_old = x;
	if (data->sky_offset > data->skybox.width)
		data->sky_offset -= data->skybox.width;
	else if (data->sky_offset < -data->skybox.width)
		data->sky_offset += data->skybox.width;
	return (0);
}
