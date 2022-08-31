#include "cub.h"

#define mapWidth 24 
#define mapHeight 24 

int	esc(int keycode, void *param)
{
	if (keycode == 65307 || keycode == 53)
		close_window(param);
	return (0);
}

// void	raycast_loop(int w, int h)
// {
// 	t_vector	*pos;
// 	t_vector	*dir;
// 	t_vector	*plane;
// 	double time = 0;
// 	double oldTime = 0;
// 	pos = init_vector(0, 0);
// 	dir = init_vector(3, 6);
// 	plane = init_vector()
// 	for(int x = 0; x < w; x++)
// 	{
// 		double cameraX = 2 * x / double(w) - 1;
// 		double rayDirX = dirX + planeX * cameraX;
// 		double rayDirY = dirY + planeY * cameraX;
// 	}
// }

int	main (void)
{
	t_data	*data;

	data = init_data(WIDTH_WINDOW, HIGTH_WINDOW);
	mlx_hook(data->var->win, 17, 0, close_window, data->var);
	mlx_hook(data->var->win, 2, 1L<<0, esc, data->var);
	// raycast_loop(WIDTH_WINDOW, HIGTH_WINDOW);
	mlx_loop(data->var->mlx);
	return (0);
}