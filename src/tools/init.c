#include "cub.h"

t_data_img	*init_img(t_vars *var, int width, int higth)
{
	t_data_img	*img;

	img = ft_calloc(sizeof(t_data), 1);
	if (!img)
	{
		ft_error(2, "error: memory allocation error in function 'init_img'", 1);
		return(NULL);
	}
	img->img = mlx_new_image(var->mlx, width, higth);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	return (img);
}

t_vars	*init_winow(int width, int higth)
{
	t_vars	*var;

	var = ft_calloc(sizeof(t_vars), 1);
	if (!var)
	{
		ft_error(2, "error: memory allocation error in function 'init_window'", 1);
		return(NULL);
	}
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, width, higth, "Spice Boys");
	return (var);
}

t_data	*init_data(int width, int higth)
{
	t_data		*data;
	t_vars		*var;
	t_data_img	*img;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
	{
		ft_error(2, "error: memory allocation error in function 'init_data'", 1);
		return (NULL);
	}
	var = init_winow(width, higth);
	img = init_img(var, width, higth);
	data->img = img;
	data->var = var;
	return (data);
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
