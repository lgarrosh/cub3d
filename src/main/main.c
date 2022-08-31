#include "cube.h"

#define mapWidth 24 
#define mapHeight 24 

int	esc(int keycode, void *param)
{
	if (keycode == 65307 || keycode == 53)
		close_window(param);
	return (0);
}

int mouse_action(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (x >= WIDTH_WINDOW || x < 0)
		return (0);
	if ( y >= HEIGTH_WINDOW || y < 0)
		return (0);
	x = ((float)x / (float)WIDTH_WINDOW) * 255 ;
	y = ((float)y / (float)HEIGTH_WINDOW ) * 255 ;
	data->other.mouse_x = x;
	data->other.mouse_y = y;
	data->other.color = create_trgb(0, y, y, x);
	return (0);
}

int	render(void *param)
{
	t_data	*data;
	int		x;
	int		y;

	x = 0;
	y = 0;
	data = (t_data *)param;
	while (y < HEIGTH_WINDOW)
	{
		while (x < WIDTH_WINDOW)
		{
			my_mlx_pixel_put(data->img, x, y, data->other.color);
			x++;
		}
		x = 0;
		data->other.color += 0.5;
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_string_put(data->mlx, data->win, 100, 100, 0x00FFFFFF, ft_itoa(data->other.mouse_x));
	mlx_string_put(data->mlx, data->win, 150, 100, 0x00FFFFFF, ft_itoa(data->other.mouse_y));
	return (0);
}

int	main (void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.other.color = 0x00000000;
	data.win = mlx_new_window(data.mlx, WIDTH_WINDOW, HEIGTH_WINDOW, "Spice Boys");
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 0, esc, &data);
	mlx_hook(data.win, 6, 0, mouse_action, &data);
	init_img(&data, WIDTH_WINDOW, HEIGTH_WINDOW);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}