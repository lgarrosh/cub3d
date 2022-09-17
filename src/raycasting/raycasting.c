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
	int	x_coord;
	int	y_coord;
	float	ray_x;
	float	ray_y;
	static int i;
	static int i2;
	int	j;
	int j2;
	t_ray *ray;


	j2 = 0;
	j = 0;
	ray = (t_ray *)lst_rays->content;
	if (ray->rad == M_PI || ray->rad == 0)
	{
		ray_x = x;
		ray_y = INT32_MAX;
	}
	else if (ray->rad == M_PI / 2 || ray->rad == 3 * M_PI / 2)
	{
		ray_x = INT32_MAX;
		ray_y = y;
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
	if (ray_x == ray_y)
	{
		ray->ray = ray_x;
		if (ray->rad > M_PI / 2 && ray->rad <= M_PI * 3 / 2)
			x_coord = (int)(data->minimap.player.x / MAP_TILE_SIZE) * MAP_TILE_SIZE - MAP_TILE_SIZE * i;
		else
			x_coord = (int)(data->minimap.player.x / MAP_TILE_SIZE) * MAP_TILE_SIZE + MAP_TILE_SIZE + MAP_TILE_SIZE * i;
		if (ray->rad > 0 && ray->rad <= M_PI)
			y_coord = (int)(data->minimap.player.y / MAP_TILE_SIZE) * MAP_TILE_SIZE - MAP_TILE_SIZE * i2;
		else
			y_coord = (int)(data->minimap.player.y / MAP_TILE_SIZE) * MAP_TILE_SIZE + MAP_TILE_SIZE + MAP_TILE_SIZE * i2;
		if (ray->rad > 0 && ray->rad <= M_PI / 2)
		{
			j = x_coord / MAP_TILE_SIZE;
			j2 = y_coord / MAP_TILE_SIZE - 1;
		}
		else if (ray->rad > M_PI / 2 && ray->rad <= M_PI)
		{
			j = x_coord / MAP_TILE_SIZE - 1;
			j2 = y_coord / MAP_TILE_SIZE - 1;
		}
		else if (ray->rad > M_PI && ray->rad <= 3 * M_PI / 2)
		{
			j = x_coord / MAP_TILE_SIZE - 1;
			j2 = y_coord / MAP_TILE_SIZE;
		}
		else if (ray->rad > 3 * M_PI / 2 && ray->rad <= 2 * M_PI)
		{
			j = x_coord / MAP_TILE_SIZE;
			j2 = y_coord / MAP_TILE_SIZE;
		}
		ray->x_end = x_coord;  // записываем координаты точки пересечения в структуру
		ray->y_end = y_coord;
		if (data->other.map[j2][j] != '1')
		{	
			i++;
			i2++;
			calculate_ray(x + MAP_TILE_SIZE, y + MAP_TILE_SIZE, data, lst_rays);
		}
	}
	else if (ray_x < ray_y)
	{	
		ray->ray = ray_x;
		if (ray->rad > M_PI / 2 && ray->rad <= M_PI * 3 / 2)
		{
			x_coord = (int)(data->minimap.player.x / MAP_TILE_SIZE) * MAP_TILE_SIZE - MAP_TILE_SIZE * i;
			ray->type = 'W';
		}
		else
		{
			x_coord = (int)(data->minimap.player.x / MAP_TILE_SIZE) * MAP_TILE_SIZE + MAP_TILE_SIZE + MAP_TILE_SIZE * i; // координаты точки пересечения
			ray->type = 'E';
		}
		y_coord = data->minimap.player.y - sin(ray->rad) * ray->ray;
		j2 = y_coord / MAP_TILE_SIZE;
		if (ray->rad > M_PI / 2 && ray->rad <= 3 * M_PI / 2)
			j = x_coord / MAP_TILE_SIZE - 1;
		else
			j = x_coord / MAP_TILE_SIZE;
		ray->x_end = x_coord;  // записываем координаты точки пересечения в структуру
		ray->y_end = y_coord;
		if (data->other.map[j2][j] != '1')
		{	
			i++;
			calculate_ray(x + MAP_TILE_SIZE, y, data, lst_rays);
		}
	}
	else
	{
		ray->ray = ray_y;
		x_coord = data->minimap.player.x + cos(ray->rad) * ray->ray;
		if (ray->rad > 0 && ray->rad <= M_PI)
		{
			y_coord = (int)(data->minimap.player.y / MAP_TILE_SIZE) * MAP_TILE_SIZE - MAP_TILE_SIZE * i2;
			ray->type = 'N';
		}
		else
		{
			y_coord = (int)(data->minimap.player.y / MAP_TILE_SIZE) * MAP_TILE_SIZE + MAP_TILE_SIZE + MAP_TILE_SIZE * i2;
			ray->type = 'S';
		}
		if (ray->rad > 0 && ray->rad <= M_PI)
			j2 = y_coord / MAP_TILE_SIZE - 1;
		else
			j2 = y_coord / MAP_TILE_SIZE;
		j = x_coord / MAP_TILE_SIZE;
		ray->x_end = x_coord;  // записываем координаты точки пересечения в структуру
		ray->y_end = y_coord;
		if (data->other.map[j2][j] != '1')
		{
			i2++;
			calculate_ray(x, y + MAP_TILE_SIZE, data, lst_rays);
		}
	}
	i = 0;
	i2 = 0;
	// mlx_string_put(data->mlx, data->win, 20,
	// 	data->minimap.img->height + 120, 0x00FF00FF, ft_itoa(ray->x_end));
	// mlx_string_put(data->mlx, data->win, 60,
	// 	data->minimap.img->height + 120, 0x00FF00FF, ft_itoa(ray->y_end));
}

void	raycasting(t_data *data)
{
	int		i;
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	data->rays = ft_lstnew(ray);
	ray->rad = data->rad;
	calculate_offset(data);
	// if (cos(data->rad) == 0 || sin(data->rad) == 0)
	// 	return ;
	i =  WIDTH_WINDOW / 2;
	while (i-- > - WIDTH_WINDOW / 2)
	{
		calculate_ray(data->minimap.x_off, data->minimap.y_off, data, ft_lstlast(data->rays));
		ray = ft_calloc(1, sizeof(t_ray));
		ray->rad = data->rad + to_radiants((double)i / 15);
		ft_lstadd_back(&data->rays, ft_lstnew(ray));
	}
}

void	floor_ceiling(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y =  0;
	while (y < HEIGTH_WINDOW / 2)
	{
		while (x < WIDTH_WINDOW)
			my_mlx_pixel_put(data->bg, x++, y, 0xFFFFFFFF);
		x = 0;
		y++;
	}
	x = 0;
	while (y < HEIGTH_WINDOW)
	{
		while (x < WIDTH_WINDOW)
			my_mlx_pixel_put(data->bg, x++, y, data->other.f_color);
		x = 0;
		y++;
	}
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
}

void draw_everything(t_data *data)
{
	t_list *copy;
	t_ray 	*ray;

	ray = (t_ray *)data->rays->content;
	copy = data->rays;

	mlx_put_image_to_window(data->mlx, data->win, data->skybox.img, data->sky_offset, 0);
	if (data->sky_offset > 0)
		mlx_put_image_to_window(data->mlx, data->win, data->skybox.img, data->sky_offset - data->skybox.width , 0);
	else if (data->sky_offset < WIDTH_WINDOW - data->skybox.width)
		mlx_put_image_to_window(data->mlx, data->win, data->skybox.img, data->sky_offset + data->skybox.width , 0);
	mlx_put_image_to_window(data->mlx, data->win, data->bg->img, 0, 0);
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

void	calculate_3d(t_data *data)
{
	int x;
	int y;
	int i;
	int color;
	t_list *lst;
	t_ray *ray;

	i = 0;
	lst = data->rays;
	ray = lst->content;
	x = 0;
	y = HEIGTH_WINDOW / 2 - 2000 / sqrt(ray->ray);
	while (x < WIDTH_WINDOW)
	{
		if (ray->type == 'W')
			color = 0x002b2b2b;
		else if (ray->type == 'E')
			color = 0x00595959;
		else if (ray->type == 'N')
			color = 0x005c4242;
		else if (ray->type == 'S')
			color = 0x00825f5f;
		while (y < HEIGTH_WINDOW / 2 + 2000 / sqrt(ray->ray))
		{
			if (y < HEIGTH_WINDOW && y > 0)
				my_mlx_pixel_put(data->bg, x, y, color);
			y++;
		}
		printf("%d\n", i++);
		lst = lst->next;
		ray = lst->content;
		y = HEIGTH_WINDOW / 2 - 2000 / sqrt(ray->ray);
		x++;
	}
}


int	raycast_loop(t_data	*data)
{
	raycasting(data);
	floor_ceiling(data);
	calculate_3d(data);
	mini_map(data, data->other.map);
	draw_everything(data);
	// put frame
	return (0);
}
