#include "cube.h"

void	init_img(t_data *data, t_data_img **img, int width, int heigth)
{
	*img = ft_calloc(sizeof(t_data_img), 1);
	if (!img)
	{
		ft_error(2, "error: memory allocation error in function 'init_img'", 1);
		return ;
	}
	(*img)->img = mlx_new_image(data->mlx, width, heigth);
	(*img)->addr = mlx_get_data_addr((*img)->img, &(*img)->bits_per_pixel, &(*img)->line_length, &(*img)->endian);
	(*img)->width = width;
	(*img)->height = heigth;
}

t_vector	init_vector(double x, double y)
{
	t_vector	vc;

	vc.x = x;
	vc.y = y;
	return (vc);
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH_WINDOW, HEIGTH_WINDOW, "Spice Boys");
	data->fps = 30;
	data->review = CORNER;
	data->grad_del = data->review / WIDTH_WINDOW;
	data->rad_del = to_radiants(data->grad_del);
	data->ray = ft_calloc(sizeof(t_ray), WIDTH_WINDOW);
	data->play.off.x = data->play.pos.x - ((int)data->play.map.x * MAP_TILE_SIZE);
	data->play.off.y = data->play.pos.y - ((int)data->play.map.y * MAP_TILE_SIZE);
	init_img(data, &data->bg, WIDTH_WINDOW, HEIGTH_WINDOW);
	data->skybox.img = mlx_xpm_file_to_image(data->mlx, "images/skybox.xpm",
		&data->skybox.width, &data->skybox.height);
	init_img(data, &data->map.img, MAP_TILE_SIZE * 7, MAP_TILE_SIZE * 7);
}

