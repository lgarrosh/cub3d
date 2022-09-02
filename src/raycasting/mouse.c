/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:07 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/02 14:08:25 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	mouse_action(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (x > WIDTH_WINDOW)
		x = WIDTH_WINDOW;
	else if (x < 0)
		x = 0;
	if (y > HEIGTH_WINDOW)
		y = HEIGTH_WINDOW;
	else if (y < 0)
		y = 0;
	data->other.mouse_x = x;
	data->other.mouse_y = y;
	return (0);
}

int	render(void *param)
{
	t_data	*data;
	int		x;
	int		y;
	int		time[2];

	x = 0;
	y = 0;
	data = (t_data *)param;
	time[0] = find_time();
	while (y < HEIGTH_WINDOW)
	{
		while (x < WIDTH_WINDOW)
		{
			my_mlx_pixel_put(data->img, x, y, 0x00000000);
			x++;
		}
		x = 0;
		y++;
	}
	line_dda(data, 0.0, 0.0, data->other.mouse_x,data->other.mouse_y);
	put_cell(data);
	time[1] = find_time();
	cufoff_frime(time, data->fps);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_string_put(data->mlx, data->win, WIDTH_WINDOW - 30,	HEIGTH_WINDOW - 18, 0x00FFFFFF,
		ft_itoa(1000 / (time[1] - time[0])));
	return (0);
}
