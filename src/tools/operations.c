#include "cube.h"

t_vector	sum_vector(t_vector v1, t_vector v2)
{
	t_vector	newvector;

	newvector = init_vector(v1.x + v2.x, v1.y + v2.y);
	return (newvector);
}
