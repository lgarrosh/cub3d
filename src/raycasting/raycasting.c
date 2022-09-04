#include "cube.h"

void	raycasting(t_data *data)
{
	(void)data;
}

void	floor_ceiling(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGTH_WINDOW / 2)
	{
		while (x < WIDTH_WINDOW)
			my_mlx_pixel_put(data->bg, x++, y, data->other.c_color);
		x = 0;
		y++;
	}
	while (y < HEIGTH_WINDOW)
	{
		while (x < WIDTH_WINDOW)
			my_mlx_pixel_put(data->bg, x++, y, data->other.f_color);
		x = 0;
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->bg->img, 0, 0);
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
	int	ver_lines[7];
	// int	x;
	int	y;

	i = 0;
	y = 0;
	while (i < 2)
	{
		ver_lines[i] = i * MAP_TILE_SIZE;
		while (y < data->minimap.img->height)
			my_mlx_pixel_put(data->minimap.img, ver_lines[i], y++, 0xA0000000);
		i++;
		y = 0;
	}
}

void	mini_map(t_data *data, char **map)
{
	int		i;
	int		j;
	float	x;
	float	y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	draw_map_bg(data);
	while (map[j] != NULL)
	{
		while (map[j][i] != '\0')
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
	mlx_string_put(data->mlx, data->win, 20,
		data->minimap.img->height + 20, 0x00FFFFFF, ft_itoa(data->minimap.x_bitmap));
	mlx_string_put(data->mlx, data->win, 40,
		data->minimap.img->height + 20, 0x00FFFFFF, ft_itoa(data->minimap.y_bitmap));
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img->img, 20, 20);
}

int	raycast_loop(t_data	*data)
{
	floor_ceiling(data);
	mini_map(data, data->other.map);
	raycasting(data);
	// put frame
	return (0);
}
