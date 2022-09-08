#include "cube.h"

t_vector	creat_vec(double x, double y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vector	vec_pix(t_vector vec)
{
	t_vector	pix;

	pix.x = vec.x * WIDTH_WINDOW / NUMBER_GRID;
	pix.y = vec.y * WIDTH_WINDOW / NUMBER_GRID;
	return (pix);
}

void	draw_grid(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x <= NUMBER_GRID)
	{
		line_dda(data->raycast, vec_pix(creat_vec(x, 0)),
			vec_pix(creat_vec(x, NUMBER_GRID)));
		x++;
	}
	while (y <= NUMBER_GRID)
	{
		line_dda(data->raycast, vec_pix(creat_vec(0, y)),
			vec_pix(creat_vec(NUMBER_GRID, y)));
		y++;
	}
}

// void	algoritm(t_data *data)
// {

// }

void	raycasting(t_data *data)
{
	draw_grid(data);
	line_dda(data->raycast, vec_pix(data->play.pos),
		vec_pix(*sum_vector(data->play.pos, data->play.dir)));
}
