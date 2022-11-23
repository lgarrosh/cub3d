/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:19:14 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/10/22 21:30:43 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_map_bg(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->map.img->height)
	{
		while (x < data->map.img->width)
			my_mlx_pixel_put(data->map.img, x++, y, 0xA0FFFFFF);
		x = 0;
		y++;
	}
}

void	draw_map_wall(float x, float y, t_data *data)
{
	double	offset_x;
	double	offset_y;
	int		paint_x;
	int		paint_y;

	paint_x = -1;
	paint_y = -1;
	offset_x = data->map.img->width / 2 - (int)data->play.pos.x;
	offset_y = data->map.img->height / 2 - (int)data->play.pos.y;
	while (++paint_y < MAP_TILE_SIZE)
	{
		if ((y + paint_y + offset_y) < data->map.img->height
			&& (y + paint_y + offset_y) >= 0)
		{
			while (++paint_x < MAP_TILE_SIZE)
			{
				if ((x + offset_x + paint_x) < data->map.img->width
					&& (x + offset_x + paint_x) >= 0)
					my_mlx_pixel_put(data->map.img, x + offset_x + paint_x,
						y + paint_y + offset_y, 0xA00FF04F);
			}		
		}
		paint_x = -1;
	}
}

void	draw_map_player(t_data *data)
{
	double	x;
	double	y;

	x = data->map.img->width / 2 - 3;
	y = data->map.img->height / 2 - 3;
	while (y < data->map.img->height / 2 + 3)
	{
		while (x < data->map.img->width / 2 + 3)
			my_mlx_pixel_put(data->map.img, x++, y, 0xA0000000);
		x = data->map.img->width / 2 - 3;
		y++;
	}
	x = 0;
	y = 0;
}

void	draw_map_grid(t_data *data)
{
	int	i;
	int	ver_lines[7];
	int	hor_lines[7];
	int	x;
	int	y;

	i = -1;
	while (++i < 7)
	{
		ft_ravno(&x, &y, 0, 0);
		hor_lines[i] = i * MAP_TILE_SIZE - data->play.pos.y + MAP_TILE_SIZE / 2;
		while (hor_lines[i] < 0)
			hor_lines[i] = data->map.img->height + hor_lines[i];
		while (hor_lines[i] > data->map.img->height)
			hor_lines[i] = data->map.img->height - hor_lines[i];
		ver_lines[i] = i * MAP_TILE_SIZE - data->play.pos.x + MAP_TILE_SIZE / 2;
		while (ver_lines[i] < 0)
			ver_lines[i] = data->map.img->width + ver_lines[i];
		while (ver_lines[i] > data->map.img->width)
			ver_lines[i] = data->map.img->width - ver_lines[i];
		while (y < data->map.img->height)
			my_mlx_pixel_put(data->map.img, ver_lines[i], y++, 0x60000000);
		while (x < data->map.img->width)
			my_mlx_pixel_put(data->map.img, x++, hor_lines[i], 0x60000000);
	}
}

void	mini_map(t_data *data, char **map)
{
	int			i;
	int			j;
	t_vector	a;

	ft_ravno(&i, &j, -1, -1);
	draw_map_bg(data);
	while (map[++j] != NULL)
	{
		if (j >= data->play.map.y - 5 && j <= data->play.map.y + 4)
		{
			while (map[j][++i] != '\0')
			{
				if (i >= data->play.map.x - 5 && i <= data->play.map.x + 4)
				{
					a = init_vector(i * MAP_TILE_SIZE, j * MAP_TILE_SIZE);
					if (map[j][i] == '1')
						draw_map_wall(a.x, a.y, data);
				}
			}
		}
		i = -1;
	}
	draw_map_grid(data);
	draw_map_player(data);
}
