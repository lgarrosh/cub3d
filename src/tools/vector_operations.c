/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:56 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/01 17:02:57 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	rev_vector(t_vector *dir, double radians)
{
	dir->x = dir->x * cos(radians) - dir->y * sin(radians);
	dir->y = dir->x * sin(radians) + dir->y * cos(radians);
}

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