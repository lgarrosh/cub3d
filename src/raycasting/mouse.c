#include "cube.h"
void	ft_skybox(int x, t_data *data);
void	draw_map_dir(t_data *data);

void	mouse_action(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	if (x >= WIDTH_WINDOW || x < 0 || x == WIDTH_WINDOW / 2)
		return ;
	// printf("%d, %d, %f\n", x, y, data->rad);
	ft_skybox(x, data);
	mlx_mouse_move(data->mlx, data->win, WIDTH_WINDOW / 2, HEIGTH_WINDOW / 2);
}

void	ft_skybox(int x, t_data *data)
{
	if (WIDTH_WINDOW / 2 < x)
		data->sky_offset -= (x - WIDTH_WINDOW / 2) * 0.3;
	else if (WIDTH_WINDOW / 2 > x)
		data->sky_offset += (WIDTH_WINDOW / 2 - x) * 0.3;
	if (data->sky_offset > data->skybox.width)
		data->sky_offset -= data->skybox.width;
	else if (data->sky_offset < -data->skybox.width)
		data->sky_offset += data->skybox.width;
	data->rad = to_radiants(data->sky_offset / 1);
	while (data->rad >= 2 * M_PI)
		data->rad -= 2 * M_PI;
	while (data->rad < 0)
		data->rad += 2 * M_PI;
}
