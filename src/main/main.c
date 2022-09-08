/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:12 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/08 15:20:12 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_collision(float x, float y, t_data *data)
{
	int	i;
	int	j;
	
	i = x / MAP_TILE_SIZE;
	j = y / MAP_TILE_SIZE;
	data->minimap.x_bitmap = i;
	data->minimap.y_bitmap = j;
	if (i >= 0 && j >= 0 && data->other.map[j][i] == '1')
		return (0);
	return (1);
}

int	keypress(int keycode, void *param)
{
	t_data	*data;
	int		speed;

	speed = 3;
	data = (t_data *)param;
	if (keycode == 65307 || keycode == 53)
		close_window(param);
	// printf("%d\n", keycode);
	if (keycode == W_KEY || keycode == 119)
		data->minimap.player.y -= speed;
	if (keycode == D_KEY || keycode == 100)
		data->minimap.player.x += speed;
	if (keycode == S_KEY || keycode == 115)
		data->minimap.player.y += speed;
	if (keycode == A_KEY || keycode == 97)
		data->minimap.player.x -= speed;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	printf("%d\n", getpid());
	if (parser(argc, argv, &data))
		return (0);
	init_data(&data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L<<0, keypress, &data);
	mlx_hook(data.win, 6, 1L<<6, mouse_action, &data);
	mlx_loop_hook(data.mlx, raycast_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
