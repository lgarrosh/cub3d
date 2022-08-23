#include "cub.h"

void    *construct(void *first, void *second);
void    *distruct(void *first, void *second);

void    *init_ve(void *first, void *second)
{
	t_vector	*vc;

	vc = malloc(sizeof(t_vector));
	if (!vc)
		return (NULL);
	if (first)
		vc->x = *(float *)first;
	if (second)
		vc->y = *(float *)second;
	return ((void *)vc);
}