/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:32:56 by preed             #+#    #+#             */
/*   Updated: 2022/09/04 15:10:42 by preed            ###   ########.fr       */
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
	int k;

	j = 0;
	k = 0;
	i = 0;
	data->other.bitmap_width = 0;
	while (map[i])
	{
		while (map[i] != '\n' && map[i] != '\0')
		{
			i++;
			j++;
		}
		if (map[i] == '\n' || map[i] != '\0')
			k++;
		if (j > data->other.bitmap_width)
			data->other.bitmap_width = j;
		j = 0;
		i++;
	}
	k++;
	data->other.bitmap_height = k;
}

void	string_to_array_of_strings(char *map, t_data *data)
{
	int	i1;
	int	i2;
	int	j;

	i1 = 0;
	i2 = 0;
	j = 0;
	data->other.map = ft_calloc(data->other.bitmap_height + 1, sizeof(char *));
	while (i1 < data->other.bitmap_height)
		data->other.map[i1++] = ft_calloc(data->other.bitmap_width + 1, sizeof(char));
	i1 = 0;
	while (map[j])
	{
		if (map[j] == '\n')
		{	
			i2 = 0;
			i1++;
		}
		else
		{
			data->other.map[i1][i2] = map[j];
			i2++;
		}
		j++;
	}
	free(map);
}

void	empty_to_dash(t_data *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (data->other.map[i] != NULL)
	{
		while (j < data->other.bitmap_width)
		{
			if (data->other.map[i][j] == ' ' || data->other.map[i][j] == '\0')
				data->other.map[i][j] = '-';
			j++;
		}
		i++;
		j = 0;
	}
	i = 0;
	while (data->other.map[i] != NULL)
		printf("%s\n", data->other.map[i++]);
}

void	find_player_cooridnates(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->other.map[i] != NULL)
	{
		while(data->other.map[i][j] != '\0')
		{
			if (data->other.map[i][j] == 'N')
			{
				data->minimap.player.x = j * MAP_TILE_SIZE + MAP_TILE_SIZE / 2;
				data->minimap.player.y = i * MAP_TILE_SIZE + MAP_TILE_SIZE / 2;
			}
			j++;
		}
		j = 0;
		i++;
	}
	printf("x = %f;y = %f\n", data->minimap.player.x, data->minimap.player.y);
}

int	save_map(char *string, int i, t_data *data)
{
	char	*map_string;

	map_string = ft_substr(string, i, ft_strlen(&string[i]));
	find_bitmap_dimensions(map_string, data);
	string_to_array_of_strings(map_string, data);
	empty_to_dash(data);
	find_player_cooridnates(data);
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