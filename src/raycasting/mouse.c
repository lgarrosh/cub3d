#include "cube.h"
void	draw_map_dir(t_data *data);

void	mouse_action(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	if (x >= WIDTH_WINDOW || x < 0 || x == WIDTH_WINDOW / 2)
		return ;
	ft_skybox(x, data);
	mlx_mouse_move(data->mlx, data->win, WIDTH_WINDOW / 2, HEIGTH_WINDOW / 2);
}

void	ft_skybox(int x, t_data *data)
{
	if (WIDTH_WINDOW / 2 < x)
		data->sky_offset += (x - WIDTH_WINDOW / 2) * MOUSE_SPEED;
	else if (WIDTH_WINDOW / 2 > x)
		data->sky_offset -= (WIDTH_WINDOW / 2 - x) * MOUSE_SPEED;
	if (data->sky_offset > data->skybox.width)
		data->sky_offset -= data->skybox.width;
	else if (data->sky_offset < -data->skybox.width)
		data->sky_offset += data->skybox.width;
	data->play.rad = to_radiants(data->sky_offset / 1);
	while (data->play.rad >= 2 * M_PI)
		data->play.rad -= 2 * M_PI;
	while (data->play.rad < 0)
		data->play.rad += 2 * M_PI;
}
