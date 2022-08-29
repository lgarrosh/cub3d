#include "cub.h"

void	my_mlx_pixel_put(t_data_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close_window(void *param)
{
	t_vars *var;

	var = (t_vars *)param;
	mlx_destroy_window(var->mlx, var->win);
	return (0);
}