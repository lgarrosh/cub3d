#include "cube.h"

t_vector	sum_vector(t_vector v1, t_vector v2)
{
	t_vector	newvector;

	newvector = init_vector(v1.x + v2.x, v1.y + v2.y);
	return (newvector);
}

double	ft_cos(double rad)
{
	if (rad == M_PI / 2 || rad == (M_PI / 2) * 3)
		rad += 0.000001;
	return(cos(rad));
}

double	ft_sin(double rad)
{
	if (rad == 0 || rad == M_PI)
		rad += 0.0000001;
	return(sin(rad));
}