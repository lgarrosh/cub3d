/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:12 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/02 13:18:34 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

#define mapWidth 24 
#define mapHeight 24 

int	esc(int keycode, void *param)
{
	if (keycode == 65307 || keycode == 53)
		close_window(param);
	return (0);
}

int	main(void)
{
	t_data	data;

	init_data(&data);
	data.other.mouse_x = 0;
	data.other.mouse_y = 0;
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L<<0, esc, &data);
	mlx_hook(data.win, 6, 0, mouse_action, &data);
	mlx_loop_hook(data.mlx, render, &data);
	// mlx_loop_hook(data.mlx, raycast_loop, &data);
	// mlx_put_image_to_window(data.mlx, data.win, data.img->img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
