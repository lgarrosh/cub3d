/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:46:43 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/10/22 21:47:14 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	uslov(t_data *data, char ch, int i, int j)
{
	data->play.map.x = j;
	data->play.map.y = i;
	data->play.pos.x = j * MAP_TILE_SIZE + MAP_TILE_SIZE / 2;
	data->play.pos.y = i * MAP_TILE_SIZE + MAP_TILE_SIZE / 2;
	data->naprav = ch;
	ft_rad(data, ch);
}

void	find_player_cooridnates(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map.map[i] != NULL)
	{
		while (data->map.map[i][j] != '\0')
		{
			if (data->map.map[i][j] == 'N')
				uslov(data, 'N', i, j);
			else if (data->map.map[i][j] == 'S')
				uslov(data, 'S', i, j);
			else if (data->map.map[i][j] == 'W')
				uslov(data, 'W', i, j);
			else if (data->map.map[i][j] == 'E')
				uslov(data, 'E', i, j);
			j++;
		}
		j = 0;
		i++;
	}
}
