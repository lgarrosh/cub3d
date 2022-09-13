#include "cube.h"

void line_dda(t_data_img *data, double x1, double y1, double x2, double y2)
{
	// Целочисленные значения координат начала и конца отрезка,
	// округленные до ближайшего целого
	int iX1 = roundf(x1);
	int iY1 = roundf(y1);
	int iX2 = roundf(x2);
	int iY2 = roundf(y2);
	// Длина и высота линии
	int deltaX = abs(iX1 - iX2);
	int deltaY = abs(iY1 - iY2);
	// Считаем минимальное количество итераций, необходимое
	// для отрисовки отрезка. Выбирая максимум из длины и высоты
	// линии, обеспечиваем связность линии
	int length = deltaX;
	if (deltaX < deltaY)
		length = deltaY;
	// особый случай, на экране закрашивается ровно один пиксел
	if (length == 0)
	{
		my_mlx_pixel_put(data, iX1, iY1, 0x00000000);
		return;
	}
	// Вычисляем приращения на каждом шаге по осям абсцисс и ординат
	double dX = (x2 - x1) / length;
	double dY = (y2 - y1) / length;
	// Начальные значения
	double x = x1;
	double y = y1;
	// Основной цикл
	length++;
	while (length--)
	{
		x += dX;
		y += dY;
		my_mlx_pixel_put(data, roundf(x), roundf(y), 0x00000000);
	}
}


void	calculate_offset(t_data *data)
{
	int	xx;
	int	yy;

	if (data->rad >= 0 && data->rad < M_PI / 2)
	{
		xx = MAP_TILE_SIZE - (int)data->minimap.player.x % MAP_TILE_SIZE;
		yy = (int)data->minimap.player.y % MAP_TILE_SIZE;
	}
	if (data->rad >= M_PI / 2 && data->rad < M_PI)
	{
		xx = (int)data->minimap.player.x % MAP_TILE_SIZE;
		yy = (int)data->minimap.player.y % MAP_TILE_SIZE;
	}
	if (data->rad >= M_PI && data->rad < 3 * M_PI / 2)
	{
		xx = (int)data->minimap.player.x % MAP_TILE_SIZE;
		yy = MAP_TILE_SIZE - (int)data->minimap.player.y % MAP_TILE_SIZE;
	}
	if (data->rad >= 3 * M_PI / 2 && data->rad < 2 * M_PI)
	{
		xx = MAP_TILE_SIZE - (int)data->minimap.player.x % MAP_TILE_SIZE;
		yy = MAP_TILE_SIZE - (int)data->minimap.player.y % MAP_TILE_SIZE;
	}
	data->minimap.x_off = xx;
	data->minimap.y_off = yy;
	mlx_string_put(data->mlx, data->win, 20,
		data->minimap.img->height + 70, 0x00FF00FF, ft_itoa(xx));
	mlx_string_put(data->mlx, data->win, 40,
		data->minimap.img->height + 70, 0x00FF00FF, ft_itoa(yy));
}

void	calculate_ray(int x, int y, t_data *data)
{
	int	x_coord;
	int	y_coord;
	int	ray_x;
	int	ray_y;

	ray_x = x / cos(data->rad);
	ray_y = y / sin(data->rad);
	if (data->rad == M_PI)
	{
		ray_x = x;
		ray_y = y;
	}
	if (data->rad == M_PI / 2 || data->rad == 3 * M_PI / 2)
		ray_x = x;
	if (ray_x < 0)
		ray_x = -ray_x;
	if (ray_y < 0)
		ray_y = -ray_y;
	if (ray_x < ray_y)
	{	
		data->ray = ray_x;
		x_coord = data->minimap.player.x + cos(data->rad) * data->ray;
		y_coord = data->minimap.player.y - sin(data->rad) * data->ray;
		if (data->other.map[y_coord / MAP_TILE_SIZE][x_coord / MAP_TILE_SIZE] != '1')
		{
			data->minimap.x_intsct = x_coord;
			data->minimap.y_intsct = y_coord;
			calculate_ray(x + MAP_TILE_SIZE, y, data);
		}
	}
	else
	{
		data->ray = ray_y;
		x_coord = data->minimap.player.x + cos(data->rad) * data->ray;
		y_coord = data->minimap.player.y - sin(data->rad) * data->ray;
		if (data->other.map[y_coord / MAP_TILE_SIZE][x_coord / MAP_TILE_SIZE] != '1')
		{
			data->minimap.x_intsct = x_coord;
			data->minimap.y_intsct = y_coord;
			calculate_ray(x, y + MAP_TILE_SIZE, data);
		}
	}
}

void	raycasting(t_data *data)
{
	calculate_offset(data);
	if (cos(data->rad) == 0 || sin(data->rad) == 0)
		return ;
	calculate_ray(data->minimap.x_off, data->minimap.y_off, data);
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
	double	offset_x;
	double	offset_y;
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
	double	x;
	double	y;

	x = data->minimap.img->width / 2 - 3;
	y = data->minimap.img->height / 2 - 3;
	while (y < data->minimap.img->height / 2 + 3)
	{
		while (x < data->minimap.img->width / 2 + 3)
			my_mlx_pixel_put(data->minimap.img, x++, y, 0xA0000000);
		x = data->minimap.img->width / 2 - 3;
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
	double	x;
	double	y;

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
	line_dda(data->minimap.img, data->minimap.img->width / 2, data->minimap.img->height / 2,
		data->minimap.img->width / 2 + data->minimap.x_intsct - data->minimap.player.x,
		data->minimap.img->height / 2 + data->minimap.y_intsct - data->minimap.player.y);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img->img, 20, 20);
	mlx_string_put(data->mlx, data->win, 60,
		data->minimap.img->height + 80, 0x0000FF00, ft_itoa(to_degrees(data->rad)));
	mlx_string_put(data->mlx, data->win, 90,
		data->minimap.img->height + 80, 0x00FFFF00, ft_itoa((data->rad)));
	mlx_string_put(data->mlx, data->win, 20,
		data->minimap.img->height + 100, 0x00FFFF00, ft_itoa((data->minimap.x_intsct)));
	mlx_string_put(data->mlx, data->win, 50,
		data->minimap.img->height + 100, 0x00FFFF00, ft_itoa((data->minimap.y_intsct)));
}

int	raycast_loop(t_data	*data)
{
	floor_ceiling(data);
	mini_map(data, data->other.map);
	raycasting(data);
	// put frame
	return (0);
}
