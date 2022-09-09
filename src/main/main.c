/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:12 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/09 11:15:44 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int worldMap[mapWidth][mapHeight];

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
	{
		if(worldMap[(int)roundf(data->play.pos.x + data->play.dir.x * data->cub.move_speed)][(int)roundf(data->play.pos.y)] == 0)
			data->play.pos.x += data->play.dir.x * data->cub.move_speed;
		if(worldMap[(int)roundf(data->play.pos.x)][(int)roundf(data->play.pos.y + data->play.dir.y * data->cub.move_speed)] == 0)
			data->play.pos.y += data->play.dir.y * data->cub.move_speed;
	}
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
