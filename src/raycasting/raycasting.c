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
		if (x > data->width || y > data->height || x < 0 || y < 0)
			return ;
		my_mlx_pixel_put(data, roundf(x), roundf(y), 0x00000000);
	}
}

// считаем и записываем в структуру изначальные отступы игрока, с помощью которых считаются
// изначальный луч (гипотенуза) от игрока до ближайшего пересечения до другой клетки
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


// считаем конечный луч до столкновения со стеной с помощью рекурсии
// подавая каждый раз увеличивающиеся значения отступа по x и y 
void	calculate_ray(int x, int y, t_data *data, t_list *lst_rays)
{
	double	x_coord;
	double	y_coord;
	double	ray_x;
	double	ray_y;
	int	j;
	t_ray *ray;

	ray = (t_ray *)lst_rays->content;
	if (ray->rad == M_PI)
	{
		ray_x = x;
		ray_y = y;
	}
	if (ray->rad == M_PI / 2 || ray->rad == 3 * M_PI / 2)
	{
		ray_x = x;
		ray_y = y / sin(ray->rad);
	}
	else 
	{
		ray_x = x / cos(ray->rad); // луч пересечения с осью Y
		ray_y = y / sin(ray->rad); // луч пересечения с осью X
	}
	if (ray_x < 0)
		ray_x = -ray_x;
	if (ray_y < 0)
		ray_y = -ray_y;
	if (ray_x <= ray_y)
	{	
		ray->ray = ray_x;
		x_coord = data->minimap.player.x + cos(ray->rad) * ray->ray; // координаты точки пересечения
		y_coord = data->minimap.player.y - sin(ray->rad) * ray->ray;
		if (ray->rad > M_PI / 2 && ray->rad <= 3 * M_PI / 2)
			j = x_coord / MAP_TILE_SIZE;
		else
			j = x_coord / MAP_TILE_SIZE - 1;
		if (data->other.map[(int)y_coord / MAP_TILE_SIZE][j] != '1')
		{
			ray->x_end = x_coord;  // записываем координаты точки пересечения в структуру
			ray->y_end = y_coord;
			calculate_ray(x + MAP_TILE_SIZE, y, data, lst_rays);
		}
	}
	else
	{
		ray->ray = ray_y;
		x_coord = data->minimap.player.x + cos(ray->rad) * ray->ray;
		y_coord = data->minimap.player.y - sin(ray->rad) * ray->ray;
		if (ray->rad > 0 && ray->rad <= M_PI)
			j = y_coord / MAP_TILE_SIZE;
		else
			j = y_coord / MAP_TILE_SIZE - 1;
		if (data->other.map[j][(int)(x_coord) / MAP_TILE_SIZE] != '1')
		{
			ray->x_end = x_coord;
			ray->y_end = y_coord;
			calculate_ray(x, y + MAP_TILE_SIZE, data, lst_rays);
		}
	}
	// x_coord = data->minimap.player.x + cos(data->rad) * data->ray;
	// y_coord = data->minimap.player.y - sin(data->rad) * data->ray;
	// data->minimap.x_intsct = x_coord;  // записываем координаты точки пересечения в структуру
	// data->minimap.y_intsct = y_coord;
	// mlx_string_put(data->mlx, data->win, 50,
	// 	data->minimap.img->height + 150, 0x00A000C0, ft_itoa((data->ray)));
}

void	raycasting(t_data *data)
{
	int		i;
	t_ray	*ray;

	i = 0;
	ray = ft_calloc(1, sizeof(t_ray));
	data->rays = ft_lstnew(ray);
	ray->rad = data->rad;
	calculate_offset(data);
	while (i++ < WIDTH_WINDOW / 2)
	{
		calculate_ray(data->minimap.x_off, data->minimap.y_off, data, ft_lstlast(data->rays));
		ray = ft_calloc(1, sizeof(t_ray));
		ray->rad = data->rad + to_radiants((double)i / 15);
		ft_lstadd_back(&data->rays, ft_lstnew(ray));
	}
	// i = 0;
	// while (i++ < WIDTH_WINDOW / 2)
	// {
	// 	calculate_ray(data->minimap.x_off, data->minimap.y_off, data, ft_lstlast(data->rays));
	// 	ray = ft_calloc(1, sizeof(t_ray));
	// 	ray->rad = data->rad - to_radiants((double)i / 15);
	// 	ft_lstadd_back(&data->rays, ft_lstnew(ray));
	// }
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
	t_list *copy;
	t_ray 	*ray;

	ray = (t_ray *)data->rays->content;
	copy = data->rays;
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
	while (copy->next)
	{
		line_dda(data->minimap.img, data->minimap.img->width / 2, data->minimap.img->height / 2,
		data->minimap.img->width / 2 + ray->x_end - data->minimap.player.x,
		data->minimap.img->height / 2 + ray->y_end - data->minimap.player.y);
		copy = copy->next;
		ray = copy->content;
	}
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
	raycasting(data);
	mini_map(data, data->other.map);
	// put frame
	return (0);
}
