#include "cube.h"

int	mouse_action(int x, int y, void *param)
{
	t_data		*data;
	static int	x_old;

	if (x >= WIDTH_WINDOW || x < 0)
		return (0);
	if ( y >= HEIGTH_WINDOW || y < 0)
		return (0);
	data = (t_data *)param;
	if (x_old < x && x_old != 0)
		data->sky_offset -= (x - x_old) * 0.5;
	else if (x_old > x && x_old != 0)
		data->sky_offset += (x_old - x) * 0.5;
	x_old = x;
	if (data->sky_offset > data->skybox.width)
		data->sky_offset -= data->skybox.width;
	else if (data->sky_offset < -data->skybox.width)
		data->sky_offset += data->skybox.width;
	data->rad = to_radiants(-data->sky_offset / 1 );
	return (0);
}
