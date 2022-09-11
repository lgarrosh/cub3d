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
	float	hip;
	int		f;

	x = data->minimap.img->width / 2 - 5;
	y = data->minimap.img->height / 2 - 5;
	while (y < data->minimap.img->height / 2 + 5)
	{
		while (x < data->minimap.img->width / 2 + 5)
			my_mlx_pixel_put(data->minimap.img, x++, y, 0xA0000000);
		x = data->minimap.img->width / 2 - 5;
		y++;
	}
	x = 0;
	y = 0;
	f = -2;
	hip = 30;
	if (cos(data->rad) < 0)
	{
		while (x > cos(data->rad) * hip)
	{
		y = tan(data->rad) * x;
		while (f < 2)
			my_mlx_pixel_put(data->minimap.img, x + data->minimap.img->width / 2,
			y + data->minimap.img->height / 2 + f++, 0xA0000000);
		x--;
		f = -2;
	}
	}
	else {
			while (x < cos(data->rad) * hip)
	{
		y = tan(data->rad) * x;
		while (f < 2)
			my_mlx_pixel_put(data->minimap.img, x + data->minimap.img->width / 2,
			y + data->minimap.img->height / 2 + f++, 0xA0000000);
		x++;
		f = -2;
	}
	}
}

void	draw_map_grid(t_data *data)
{
	int	i;
	int	ver_lines[7];
	int	hor_lines[7];
	int	x;
	int	y;

	i = 0;
	y = 0;
	x = 0;
	while (i < 7)
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
		if (j >= data->minimap.y_bitmap - 4
			&& j <= data->minimap.y_bitmap + 4)
		{
			while (map[j][i] != '\0')
			{
				if (i >= data->minimap.x_bitmap - 4
					&& i <= data->minimap.x_bitmap + 4)
				{
					x = i * MAP_TILE_SIZE;
					y = j * MAP_TILE_SIZE;
					if (map[j][i] == '1')
						draw_map_wall(x, y, data);
				}
				i++;
			}
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
	mlx_string_put(data->mlx, data->win, 20,
		data->minimap.img->height + 40, 0x00FFFFFF, ft_itoa(data->minimap.player.x));
	mlx_string_put(data->mlx, data->win, 60,
		data->minimap.img->height + 40, 0x00FFFFFF, ft_itoa(data->minimap.player.y));
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img->img, 20, 20);
	mlx_string_put(data->mlx, data->win, 60,
		data->minimap.img->height + 80, 0x00FFFFFF, ft_itoa(-to_degrees(data->rad)));
}

int	raycast_loop(t_data	*data)
{
	floor_ceiling(data);
	mini_map(data, data->other.map);
	raycasting(data);
	// put frame
	return (0);
}
