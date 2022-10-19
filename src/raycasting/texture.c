#include "cube.h"

void	load_img(t_data *data, t_data_img *img, int **texture)
{
	int	x;
	int	y;

	y = 0;
    (void)data;
    texture[0] = (int *)ft_calloc(sizeof(int), img->width * img->height);
	img->addr = mlx_get_data_addr(img->img, \
		&img->bits_per_pixel, &img->line_length, &img->endian);
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[0][img->width * y + x] = ((int *)img->addr)[img->width * y + x];
			x++;
		}
		y++;
	}
}