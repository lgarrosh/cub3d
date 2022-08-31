#include "cube.h"

void	init_img(t_data *data, int width, int heigth)
{
	t_data_img *img;

	data->img = ft_calloc(sizeof(t_data_img), 1);
	img = data->img;
	if (!img)
	{
		ft_error(2, "error: memory allocation error in function 'init_img'", 1);
		return ;
	}
	img->img = mlx_new_image(data->mlx, width, heigth);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
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
