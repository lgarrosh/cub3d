/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:03 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/02 13:49:08 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void	floor_ceiling(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y =  HEIGTH_WINDOW / 2 - 1;
	while (y < HEIGTH_WINDOW)
	{
		while (x < WIDTH_WINDOW)
			my_mlx_pixel_put(data->bg, x++, y, data->other.f_color);
		x = 0;
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->bg->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->skybox.img, data->sky_offset, 0);
	if (data->sky_offset > 0)
		mlx_put_image_to_window(data->mlx, data->win, data->skybox.img, data->sky_offset - data->skybox.width , 0);
	else if (data->sky_offset < WIDTH_WINDOW - data->skybox.width)
		mlx_put_image_to_window(data->mlx, data->win, data->skybox.img, data->sky_offset + data->skybox.width , 0);
}

void	draw_map_bg(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->minimap.img->height)
	{
		while (x < data->minimap.img->width)
			my_mlx_pixel_put(data->minimap.img, x++, y, 0xA0FFFFFF);
		x = 0;
		y++;
	}
}

void	draw_map_wall(float x, float y, t_data *data)
{
	float	offset_x;
	float	offset_y;
	int		paint_x;
	int		paint_y;

	paint_x = 0;
	paint_y = 0;
	offset_x = data->minimap.img->width / 2 - data->minimap.player.x;
	offset_y = data->minimap.img->height / 2 - data->minimap.player.y;
	while (paint_y < MAP_TILE_SIZE)
	{
		if ((y + paint_y + offset_y) < data->minimap.img->height
			&& (y + paint_y + offset_y) >= 0)
		{
			while (paint_x < MAP_TILE_SIZE)
			{
				if ((x + offset_x + paint_x) < data->minimap.img->width
					&& (x + offset_x + paint_x) >= 0)
					my_mlx_pixel_put(data->minimap.img, x + offset_x + paint_x,
						y + paint_y + offset_y, 0xA00FF04F);
				paint_x++;
			}		
		}
		paint_y++;
		paint_x = 0;
	}
}

void	draw_map_player(t_data *data)
{
	float	x;
	float	y;

	x = data->minimap.img->width / 2 - 5;
	y = data->minimap.img->height / 2 - 5;
	while (y < data->minimap.img->height / 2 + 5)
	{
		while (x < data->minimap.img->width / 2 + 5)
			my_mlx_pixel_put(data->minimap.img, x++, y, 0xA0000000);
		x = data->minimap.img->width / 2 - 5;
		y++;
	}
}

void	draw_map_grid(t_data *data)
{
	int	i;
	int	ver_lines[NUMBER_OF_CELLS];
	int	hor_lines[NUMBER_OF_CELLS];
	int	x;
	int	y;

	i = 0;
	y = 0;
	x = 0;
	while (i < NUMBER_OF_CELLS)
	{
		hor_lines[i] = i * MAP_TILE_SIZE - data->minimap.player.y + MAP_TILE_SIZE / 2;
		while (hor_lines[i] < 0)
			hor_lines[i] = data->minimap.img->height + hor_lines[i];
		while (hor_lines[i] > data->minimap.img->height)
			hor_lines[i] = data->minimap.img->height - hor_lines[i];
		ver_lines[i] = i * MAP_TILE_SIZE - data->minimap.player.x + MAP_TILE_SIZE / 2;
		while (ver_lines[i] < 0)
			ver_lines[i] = data->minimap.img->width + ver_lines[i];
		while (ver_lines[i] > data->minimap.img->width)
			ver_lines[i] = data->minimap.img->width - ver_lines[i];
		while (y < data->minimap.img->height)
			my_mlx_pixel_put(data->minimap.img, ver_lines[i], y++, 0x60000000);
		while (x < data->minimap.img->width)
			my_mlx_pixel_put(data->minimap.img, x++, hor_lines[i], 0x60000000);
		i++;
		y = 0;
		x = 0;
		// printf("%d\n", i);
	}
}

void	draw_map_dir(t_data *data)
{
	t_vector	pos_player;
	t_vector	dir;
	t_vector	*pos_dir;

	dir = data->minimap.dir;
	pos_player.x = data->minimap.img->width / 2;
	pos_player.y = data->minimap.img->height / 2;
	pos_dir = sum_vector(dir, pos_player);
	line_dda(data->minimap.img, pos_player.x, pos_player.y, pos_dir->x, pos_dir->y);
}

void	mini_map(t_data *data, char **map)
{
	int		i;
	int		j;
	float	x;
	float	y;

	x = 0;
	y = 0;
	i = data->minimap.x_bitmap - NUMBER_OF_CELLS / 2 - 1;
	j = data->minimap.y_bitmap - NUMBER_OF_CELLS / 2 - 1;
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	draw_map_bg(data);
	while (j != data->minimap.y_bitmap + NUMBER_OF_CELLS / 2 + 2
		&& map[j] != NULL)
	{
		while (i != data->minimap.x_bitmap + NUMBER_OF_CELLS / 2 + 2
			&& map[j][i] != '\0')
		{
			x = i * MAP_TILE_SIZE;
			y = j * MAP_TILE_SIZE;
			if (map[j][i] == '1')
				draw_map_wall(x, y, data);
			i++;
		}
		j++;
		i = 0;
	}
	draw_map_grid(data);
	draw_map_player(data);
	draw_map_dir(data);
}

void	put_frime(t_data *data, int *time)
{
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img->img, 20, 20);
	mlx_string_put(data->mlx, data->win, 20,
		data->minimap.img->height + 20, 0x00777777, ft_itoa(data->minimap.x_bitmap));
	mlx_string_put(data->mlx, data->win, 40,
		data->minimap.img->height + 20, 0x00777777, ft_itoa(data->minimap.y_bitmap));
	mlx_string_put(data->mlx, data->win, 20,
		data->minimap.img->height + 40, 0x00FFFFFF, ft_itoa(data->minimap.player.x));
	mlx_string_put(data->mlx, data->win, 60,
		data->minimap.img->height + 40, 0x00FFFFFF, ft_itoa(data->minimap.player.y));
	mlx_string_put(data->mlx, data->win, WIDTH_WINDOW - 50,
		HEIGTH_WINDOW - 18, 0x00FFFFFF, ft_itoa(1000 / (time[1] - time[0])));
}

int	raycast_loop(t_data	*data)
{
	int	time[2];

	time[0] = find_time();
	floor_ceiling(data);
	mini_map(data, data->other.map);
	time[1] = find_time();
	cufoff_frime(time, data->fps);
	put_frime(data, time);
	return (0);
}
