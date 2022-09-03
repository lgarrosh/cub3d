/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:56 by preed             #+#    #+#             */
/*   Updated: 2022/09/02 18:59:23 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	string_to_rgb(char *rgb_s)
{
	int	rgb;
	int	r;
	int	g;
	int	b;

	rgb = 0;
	r = ft_atoi(&rgb_s[0]);
	g = ft_atoi(&rgb_s[4]);
	b = ft_atoi(&rgb_s[8]);
	rgb = r << 16;
	rgb += g << 8;
	rgb += b; 
	return (rgb);
}

int	save_map(char *string, int i, t_data *data)
{
	data->other.map = ft_substr(string, i, ft_strlen(&string[i]));
	return (0);
}

int	save_color(char *string, int i, t_data *data, char f_or_c)
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
		rgb[j][k] = '\0';
		j++;
		k = 0;
	}
	if (f_or_c == 'f')
		data->other.f_color = string_to_rgb((char *)rgb);
	else
		data->other.c_color = string_to_rgb((char *)rgb);
	return (0);
}