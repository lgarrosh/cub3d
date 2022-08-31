#include "cube.h"

void	init_img(t_data *data, int width, int heigth)
{
	
	data->img = ft_calloc(sizeof(t_data_img), 1);
	if (!data->img)
	{
		ft_error(2, "error: memory allocation error in function 'init_img'", 1);
		return ;
	}
	data->img->img = mlx_new_image(data->mlx, width, heigth);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_length,
								&data->img->endian);
}

t_vector	*init_vector(double x, double y)
{
	t_vector	*vc;

	vc = malloc(sizeof(t_vector));
	if (!vc)
		return (NULL);
	vc->x = x;
	vc->y = y;
	return (vc);
}
