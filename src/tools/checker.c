/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:56 by preed             #+#    #+#             */
/*   Updated: 2022/09/14 15:54:14 by preed            ###   ########.fr       */
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

void	find_bitmap_dimensions(char *map, t_data *data)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	k = 0;
	i = 0;
	data->map.bitmap_width = 0;
	while (map[i])
	{
		while (map[i] != '\n' && map[i] != '\0')
		{
			i++;
			j++;
		}
		if (map[i] == '\n' || map[i] != '\0')
			k++;
		if (j > data->map.bitmap_width)
			data->map.bitmap_width = j;
		j = 0;
		i++;
	}
	k++;
	data->map.bitmap_height = k;
}

void	string_to_array_of_strings(char *map, t_data *data)
{
	int	i1;
	int	i2;
	int	j;

	i1 = -1;
	i2 = 0;
	j = -1;
	data->map.map = ft_calloc(data->map.bitmap_height + 1, sizeof(char *));
	while (++i1 < data->map.bitmap_height)
		data->map.map[i1] = ft_calloc(data->map.bitmap_width + 1, sizeof(char));
	i1 = 0;
	while (map[++j])
	{
		if (map[j] == '\n')
		{	
			i2 = 0;
			i1++;
		}
		else
		{
			data->map.map[i1][i2] = map[j];
			i2++;
		}
	}
	free(map);
}

void	empty_to_dash(t_data *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (data->map.map[i] != NULL)
	{
		while (j < data->map.bitmap_width)
		{
			if (data->map.map[i][j] == ' ' || data->map.map[i][j] == '\0')
				data->map.map[i][j] = '-';
			j++;
		}
		i++;
		j = 0;
	}
	i = 0;
}

void	ft_rad(t_data *data, char ch)
{
	if (ch == 'N')
		data->sky_offset = 270;
	if (ch == 'S')
		data->sky_offset = 90;
	if (ch == 'W')
		data->sky_offset = 180;
	if (ch == 'E')
		data->sky_offset = 0;
	data->play.rad = to_radiants(data->sky_offset / 1);
	while (data->play.rad >= 2 * M_PI)
		data->play.rad -= 2 * M_PI;
	while (data->play.rad < 0)
		data->play.rad += 2 * M_PI;
}
