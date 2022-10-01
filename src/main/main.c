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
	if ((keycode == W_KEY || keycode == 119)
		&& check_collision(data->minimap.player.x, data->minimap.player.y - speed * sin(data->rad), data)
		&& check_collision(data->minimap.player.x + speed * cos(data->rad), data->minimap.player.y, data))
		{
			data->minimap.player.y -= speed * sin(data->rad);
			data->minimap.player.x += speed * cos(data->rad);
		}
	if ((keycode == D_KEY || keycode == 100)
		&& check_collision(data->minimap.player.x - speed * cos(data->rad + M_PI / 2), data->minimap.player.y, data)
		&& check_collision(data->minimap.player.x, data->minimap.player.y + speed * sin(data->rad + M_PI / 2), data))
		{
			data->minimap.player.y += speed * sin(data->rad + M_PI / 2);
			data->minimap.player.x -= speed * cos(data->rad + M_PI / 2);
		}
	if ((keycode == S_KEY || keycode == 115)
		&& check_collision(data->minimap.player.x, data->minimap.player.y - speed * sin(data->rad + M_PI), data)
		&& check_collision(data->minimap.player.x + speed * cos(data->rad + M_PI), data->minimap.player.y, data))
		{
			data->minimap.player.y -= speed * sin(data->rad + M_PI);
			data->minimap.player.x += speed * cos(data->rad + M_PI);
		}
	if ((keycode == A_KEY || keycode == 97)
		&& check_collision(data->minimap.player.x - speed * cos(data->rad - M_PI / 2), data->minimap.player.y, data)
		&& check_collision(data->minimap.player.x, data->minimap.player.y + speed * sin(data->rad - M_PI / 2), data))
		{
			data->minimap.player.y += speed * sin(data->rad - M_PI / 2);
			data->minimap.player.x -= speed * cos(data->rad - M_PI / 2);
		}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	printf("%d\n", getpid());
	if (parser(argc, argv, &data))
		return (0);
	init_data(&data);
	mlx_hook(data.win, 17, 0, close_window, &data); // закрывает программу
	mlx_hook(data.win, 2, 1L<<0, keypress, &data); // отслеживает нажатие клавиш
	mlx_hook(data.win, 6, 1L<<6, mouse_action, &data); // обрабатывает взаимодействие с мышкой
	// ***основной цикл игры***
	mlx_loop_hook(data.mlx, raycast_loop, &data);
	// ***основной цикл игры***
	mlx_loop(data.mlx);
	return (0);
}