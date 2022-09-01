/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:12 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/01 20:20:41 by lgarrosh         ###   ########.fr       */
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
	// printf("%d\n", find_time());
	// usleep(1000000);
	// printf("%d\n", find_time());
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L<<0, esc, &data);
	mlx_hook(data.win, 6, 0, mouse_action, &data);
	mlx_loop_hook(data.mlx, render, &data);
	// mlx_loop_hook(data.mlx, raycast_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
