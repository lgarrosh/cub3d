#include "cube.h"

void	forward(t_data	*data)
{
	
}

void	back(t_data *data)
{
	
}

void	right(t_data *data, int radians)
{
	t_vector	*dir;

	dir = &data->play.dir;
	dir->x = dir->x * cos(radians) - dir->y * sin(radians);
	dir->y = dir->x * sin(radians) + dir->y * cos(radians);
}

void	left(t_data *data, int radians)
{
	t_vector	*dir;

	dir = &data->play.dir;
	dir->x = dir->x * cos(radians) + dir->y * sin(radians);
	dir->y = dir->x * sin(radians) - dir->y * cos(radians);
}
