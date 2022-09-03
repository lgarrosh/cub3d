#include "cube.h"

void	my_mlx_pixel_put(t_data_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close_window(t_data *data)
{
	// free(data->img);
	mlx_destroy_window(data->mlx, data->win);
	exit(1);
	return (0);
}