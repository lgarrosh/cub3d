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

void	init_data(t_data *data)
{
	t_player	play;

	init_player(&play);
	data->play = play;
	data->rad = 0;
	data->mlx = mlx_init();
	data->fps = 30;
	data->win = mlx_new_window(data->mlx, WIDTH_WINDOW, HEIGTH_WINDOW, "Spice Boys");
	init_img(data, &data->bg, WIDTH_WINDOW, HEIGTH_WINDOW);
	data->skybox.img = mlx_xpm_file_to_image(data->mlx, "images/skybox.xpm",
		&data->skybox.width, &data->skybox.height);
	init_img(data, &data->minimap.img, MAP_TILE_SIZE * 7, MAP_TILE_SIZE * 7);
}

void	init_player(t_player *play)
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;

	pos.x = 0;
	pos.y = 0;
	dir.x = pos.x + 2;
	dir.y = pos.y + 0;
	plane.x = dir.x + 0;
	plane.y = dir.y + -0.5;
	play->pos = pos;
	play->dir = dir;
	play->plane = plane;
}
