#include "cube.h"

void	raycasting(t_data *data)
{
	(void)data;
}

void	floor_ceiling(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGTH_WINDOW / 2)
	{
		while (x < WIDTH_WINDOW)
			my_mlx_pixel_put(data->bg, x++, y, data->other.c_color);
		x = 0;
		y++;
	}
	while (y < HEIGTH_WINDOW)
	{
		while (x < WIDTH_WINDOW)
			my_mlx_pixel_put(data->bg, x++, y, data->other.f_color);
		x = 0;
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->bg->img, 0, 0);
}

void	mini_map(t_data *data, char *map)
{
	int	x;
	int	y;
	// int	i;
	(void)map;

	x = 0;
	y = 0;
	while (y < data->minimap.img->height)
	{
		while (x < data->minimap.img->width)
			my_mlx_pixel_put(data->minimap.img, x++, y, 0xA0FFFFFF);
		x = 0;
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img->img, 20, 20);
}

int	raycast_loop(t_data	*data)
{
	floor_ceiling(data);
	mini_map(data, data->other.map);
	raycasting(data);
	// put frame
	return (0);
}
