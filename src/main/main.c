#include "cube.h"
int key_release(int keycode, void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (keycode == W_KEY || keycode == 119)
		data->play.forward = 0;
	else if (keycode == S_KEY || keycode == 115)
		data->play.back = 0;
	else if (keycode == D_KEY || keycode == 100)
		data->play.right = 0;
	else if (keycode == A_KEY || keycode == 97)
		data->play.left = 0;
	else if (keycode == 65363)
		data->play.turn_l = 0;
	else if (keycode == 65361)
		data->play.turn_r = 0;
	return (0);
}

int	ft_go(t_data *data, t_vector move)
{
	t_vector	map;
	t_vector	pos;

	pos = sum_vector(data->play.pos, move);
	map.x = pos.x / MAP_TILE_SIZE;
	map.y = pos.y / MAP_TILE_SIZE;
	if (data->map.map[(int)map.y][(int)map.x] == '1')
		return (1);
	data->play.pos = pos;
	data->play.map = map;
	return (0);
}

int	keypress(int keycode, void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (keycode == 65307 || keycode == 53)
		close_window(param);
	if (keycode == W_KEY || keycode == 119)
		data->play.forward = 1;
	else if (keycode == S_KEY || keycode == 115)
		data->play.back = 1;
	else if (keycode == D_KEY || keycode == 100)
		data->play.right = 1;
	else if (keycode == A_KEY || keycode == 97)
		data->play.left = 1;
	else if (keycode == 65363)
		data->play.turn_l = 1;
	else if (keycode == 65361)
		data->play.turn_r = 1;
	return (0);
}

void	move(t_data *data)
{
	t_vector	move;

	if (data->play.forward)
	{
		move.x = SPEED * cos(data->play.rad);
		move.y = SPEED * -sin(data->play.rad);
		ft_go(data, move);
	}
	if (data->play.back)
	{
		move.x = SPEED * -cos(data->play.rad);
		move.y = SPEED * sin(data->play.rad);
		ft_go(data, move);
	}
	if (data->play.right)
	{
		move.x = SPEED * cos(data->play.rad - M_PI / 2);
		move.y = SPEED * -sin(data->play.rad - M_PI / 2);
		ft_go(data, move);
	}
	if (data->play.left)
	{
		move.x = SPEED * cos(data->play.rad + M_PI / 2);
		move.y = SPEED * -sin(data->play.rad + M_PI / 2);
		ft_go(data, move);
	}
	if (data->play.turn_l)
		ft_skybox((WIDTH_WINDOW / 2) + 10, data);
	if (data->play.turn_r)
		ft_skybox((WIDTH_WINDOW / 2) - 10, data);
	data->play.off.x = data->play.pos.x - ((int)data->play.map.x * MAP_TILE_SIZE);
	data->play.off.y = data->play.pos.y - ((int)data->play.map.y * MAP_TILE_SIZE);
}
// int	keypress(int keycode, void *param)
// {
// 	t_data		*data;
// 	t_vector	move;

// 	data = (t_data *)param;
// 	if (keycode == 65307 || keycode == 53)
// 		close_window(param);
// 	if (keycode == W_KEY || keycode == 119)
// 	{
// 		move.x = SPEED * cos(data->play.rad);
// 		move.y = SPEED * -sin(data->play.rad);
// 		ft_go(data, move);
// 	}
// 	if (keycode == S_KEY || keycode == 115)
// 	{
// 		move.x = SPEED * -cos(data->play.rad);
// 		move.y = SPEED * sin(data->play.rad);
// 		ft_go(data, move);
// 	}
// 	if (keycode == D_KEY || keycode == 100)
// 	{
// 		move.x = SPEED * cos(data->play.rad - M_PI / 2);
// 		move.y = SPEED * -sin(data->play.rad - M_PI / 2);
// 		ft_go(data, move);
// 	}
// 	if (keycode == A_KEY || keycode == 97)
// 	{
// 		move.x = SPEED * cos(data->play.rad + M_PI / 2);
// 		move.y = SPEED * -sin(data->play.rad + M_PI / 2);
// 		ft_go(data, move);
// 	}
// 	if (keycode == 65363)
// 		ft_skybox((WIDTH_WINDOW / 2) + 10, data);
// 	if (keycode == 65361)
// 		ft_skybox((WIDTH_WINDOW / 2) - 10, data);
// 	data->play.off.x = data->play.pos.x - ((int)data->play.map.x * MAP_TILE_SIZE);
// 	data->play.off.y = data->play.pos.y - ((int)data->play.map.y * MAP_TILE_SIZE);
// 	return (0);
// }

int	main(int argc, char *argv[])
{
	t_data	data;

	init_data(&data);
	if (parser(argc, argv, &data))
		return (0);
	printf("%d\n", data.walls[0].width);
	mlx_mouse_hide(data.mlx, data.win);
	mlx_hook(data.win, 17, 0, &close_window, &data); // закрывает программу
	mlx_hook(data.win, 2, 1L<<0, &keypress, &data); // отслеживает нажатие клавиш
	// mlx_hook(data.win, 6, 1L<<6, mouse_action, &data); // обрабатывает взаимодействие с мышкой
	// ***основной цикл игры***
	load_img(&data, &data.walls[0], data.texture);
	mlx_loop_hook(data.mlx, raycast_loop, &data);
	mlx_hook(data.win, 3, 1L << 1, &key_release, &data);
	// ***основной цикл игры***
	mlx_loop(data.mlx);
	return (0);
}