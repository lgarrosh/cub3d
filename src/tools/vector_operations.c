#include "cube.h"

double	mod_vectir(t_vector	vec)
{
	double	mod;
	int		x;
	int		y;
	
	x = vec.x * vec.x;
	y = vec.y * vec.y;
	mod = sqrt(x + y);
	return (mod);
}

t_vector	*sum_vector(t_vector v1, t_vector v2)
{
	t_vector	*newvector;

	newvector = init_vector(v1.x + v2.x, v1.y + v2.y);
	return (newvector);
}

void	umnoj_v(t_vector *v, double nb)
{
	v->x = v->x * nb;
	v->y = v->y * nb;
}