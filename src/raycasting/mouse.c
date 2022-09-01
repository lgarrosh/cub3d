/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:07 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/01 20:30:27 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	mouse_action(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (x >= WIDTH_WINDOW || x < 0)
		return (0);
	if (y >= HEIGTH_WINDOW || y < 0)
		return (0);
	x = ((float)x / (float)WIDTH_WINDOW) * 255 ;
	y = ((float)y / (float)HEIGTH_WINDOW) * 255 ;
	data->other.mouse_x = x;
	data->other.mouse_y = y;
	data->other.color = create_trgb(0, y, x, x);
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
			my_mlx_pixel_put(data->img, x, y, data->other.color);
			x++;
		}
		x = 0;
		data->other.color += 0.5;
		y++;
	}
	time[1] = find_time();
	cufoff_frime(time, data->fps);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_string_put(data->mlx, data->win, 100, 100, 0x00FFFFFF,
		ft_itoa(data->other.mouse_x));
	mlx_string_put(data->mlx, data->win, 150, 100, 0x00FFFFFF,
		ft_itoa(data->other.mouse_y));
	mlx_string_put(data->mlx, data->win, WIDTH_WINDOW - 30,	HEIGTH_WINDOW - 18, 0x00FFFFFF,
		ft_itoa(1000 / (time[1] - time[0])));
	return (0);
}
