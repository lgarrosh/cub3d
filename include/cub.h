#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef void				(*t_operations)(void *, void *);

typedef struct s_vector
{
	float			x;
	float			y;
}			t_vector;

typedef struct s_MLX_data
{
	
}			t_data;