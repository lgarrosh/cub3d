/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:51 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/01 20:22:53 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	find_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec % 100000) * 1000 + t.tv_usec / 1000);
}

void	ft_sleep(int time)
{
	int	tmp;

	tmp = find_time();
	while (1)
	{
		if ((find_time() - tmp) >= time)
			break ;
		usleep(100);
	}
}
// отсечка кадров 
void	cufoff_frime(int *time, int fps)
{
	int	time_sleep;

	time_sleep = time[0] + 1000 / fps - time[1];
	if (time_sleep > 0)
	{
		ft_sleep(time_sleep);
		time[1] = find_time();
	}
}
