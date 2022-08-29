#include "cub.h"

#define mapWidth 24 
#define mapHeight 24 

int	esc(int keycode, void *param)
{
	if (keycode == 65307 || keycode == 53)
		close_window(param);
	return (0);
}

int	main (void)
{
	t_vars	*var;
	t_data	*img;

	var = init_winow(WIDTH_WINDOW, HIGTH_WINDOW);
	img = init_img(var, WIDTH_WINDOW,HIGTH_WINDOW);
	(void)img;
	mlx_hook(var->win, 17, 0, close_window, var);
	mlx_hook(var->win, 2, 1L<<0, esc, var);
	mlx_loop(var->mlx);
	return (0);
}