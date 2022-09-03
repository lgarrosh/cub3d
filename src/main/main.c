#include "cube.h"

int	esc(int keycode, void *param)
{
	if (keycode == 65307 || keycode == 53)
		close_window(param);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parser(argc, argv, &data))
		return (0);
	init_data(&data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L<<0, esc, &data);
	mlx_hook(data.win, 6, 0, mouse_action, &data);
	// mlx_loop_hook(data.mlx, render, &data);
	mlx_loop_hook(data.mlx, raycast_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}