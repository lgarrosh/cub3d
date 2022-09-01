/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:56 by preed             #+#    #+#             */
/*   Updated: 2022/09/01 22:03:52 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	string_to_rgb(char *rgb_s, t_data *data)
{
	// int	rgb;
	int	r;
	int	g;
	int	b;
	(void)data;

	r = ft_atoi(&rgb_s[0]);
	g = ft_atoi(&rgb_s[4]);
	b = ft_atoi(&rgb_s[8]);
	printf("r = %d, g = %d, b = %d\n", r, g, b);
}

int	save_map(char *string, int i, t_data *data)
{
	(void)data;
	while (string[i] != '\0')
		write(1, &string[i++], 1);
	return (0);
}

int	save_ceiling_color(char *string, int i, t_data *data)
{
	char	rgb[3][4];
	int		j;
	int		k;

	j = 0;
	k = 0;
	(void)data;

	while (string[i] != '\n')
	{
		while (!ft_isdigit(string[i]))
			i++;
		while (ft_isdigit(string[i]))
			rgb[j][k++] = string[i++];
		while (k <= 2)
			rgb[j][k++] = '.';
		j++;
		rgb[j][k] = '\0';
		k = 0;
	}
	string_to_rgb((char *)rgb, data);
	return (0);
}

int	save_floor_color(char *string, int i, t_data *data)
{
	(void)data;

	while (string[i] != '\n')
		write(1, &string[i++], 1);
	return (0);
}