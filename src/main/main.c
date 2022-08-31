#include "cube.h"

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
	t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH_WINDOW, HEIGTH_WINDOW, "Spice Boys");
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L<<0, esc, &data);
	init_img(&data, 300, 200);
	my_mlx_pixel_put(data.img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(data.mlx, data.win, data.img->img, 0, 0);
	mlx_loop(data.mlx);

	return (0);
}