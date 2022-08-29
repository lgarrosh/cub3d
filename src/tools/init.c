#include "cub.h"

t_data	*init_img(t_vars *var, int width, int higth)
{
	t_data	*img;

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