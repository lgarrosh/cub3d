/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arman <arman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:27:42 by arman             #+#    #+#             */
/*   Updated: 2022/10/22 06:54:06 by arman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	find_bitmap_dimensions(char *map, t_data *data);
void	string_to_array_of_strings(char *map, t_data *data);
void	empty_to_dash(t_data *data);
void	find_player_cooridnates(t_data *data);

int	check_symbols(char *map)
{
	int	player;

	player = 0;
	while (*map)
	{
		if (*map != '1' && *map != '0'
			&& *map != 'N' && *map != 'W'
			&& *map != 'S' && *map != 'E'
			&& *map != ' ' && *map != '\n')
			return (1);
		if (*map == 'N' || *map == 'W'
			|| *map == 'S' || *map == 'E')
			player++;
		map++;
	}
	if (player != 1)
		return (1);
	return (0);
}

int	check_walls_t(int x, int y, int j, char **map)
{
	int	i;

	i = -1;
	j = -1;
	while (++j < y)
	{
		while (++i < x)
			if (((i == 0 || j == 0) || (i == x - 1 || j == y - 1))
				&& (map[j][i] != '1' && map[j][i] != '-'))
				return (1);
		i = -1;
	}
	i = -1;
	j = -1;
	while (++j < y)
	{
		while (++i < x)
			if (((i != 0 && j != 0) && (i != x - 1 && j != y - 1))
				&& (map[j][i + 1] == '-' || map[j][i - 1] == '-'
				|| map[j + 1][i] == '-' || map[j - 1][i] == '-')
				&& (map[j][i] != '1' && map[j][i] != '-'))
				return (1);
		i = -1;
	}
	return (0);
}

int	check_walls(t_data *data)
{
	int		x;
	int		y;
	int		j;
	char	**map;

	x = data->map.bitmap_width;
	y = data->map.bitmap_height;
	map = data->map.map;
	j = -1;
	return (check_walls_t(x, y, j, map));
}

int	save_map(char *string, int i, t_data *data)
{
	char	*map_string;

	map_string = ft_substr(string, i, ft_strlen(&string[i]));
	if (check_symbols(map_string))
		return (1);
	find_bitmap_dimensions(map_string, data);
	string_to_array_of_strings(map_string, data);
	empty_to_dash(data);
	if (check_walls(data))
		return (1);
	find_player_cooridnates(data);
	return (0);
}
