#include "cube.h"

void	calculate_off(t_data *data, t_ray *ray);
void	calculate_ray(t_data *data, t_ray *ray);

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
/*
// считаем и записываем в структуру изначальные отступы игрока, с помощью которых считаются
// изначальный луч (гипотенуза) от игрока до ближайшего пересечения до другой клетки
void	calculate_offset(t_data *data)
{
	int	xx;
	int	yy;

	xx = 0;
	yy = 0;
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
void	calculate_ray(int x, int y, t_data *data, t_ray *ray)
{
	(void)x;
	(void)y;
	(void)data;
	ray->x_end = 15;
	ray->y_end = 15;
	ray->ray = 10;
	// mlx_string_put(data->mlx, data->win, 20,
	// 	data->minimap.img->height + 120, 0x00FF00FF, ft_itoa(ray->x_end));
	// mlx_string_put(data->mlx, data->win, 60,
	// 	data->minimap.img->height + 120, 0x00FF00FF, ft_itoa(ray->y_end));
}

*/
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
			my_mlx_pixel_put(data->bg, x++, y, data->f_color);
		x = 0;
		y++;
	}
}

void	draw_map_bg(t_data *data) // рисует фон мини карты 
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

void	draw_map_wall(float x, float y, t_data *data) // рисует стены на миникарте 
{
	double	offset_x;
	double	offset_y;
	int		paint_x;
	int		paint_y;

	paint_x = 0;
	paint_y = 0;
	offset_x = data->map.img->width / 2 - data->play.pos.x;
	offset_y = data->map.img->height / 2 - data->play.pos.y;
	while (paint_y < MAP_TILE_SIZE)
	{
		if ((y + paint_y + offset_y) < data->map.img->height
			&& (y + paint_y + offset_y) >= 0)
		{
			while (paint_x < MAP_TILE_SIZE)
			{
				if ((x + offset_x + paint_x) < data->map.img->width
					&& (x + offset_x + paint_x) >= 0)
					my_mlx_pixel_put(data->map.img, x + offset_x + paint_x,
						y + paint_y + offset_y, 0xA00FF04F);
				paint_x++;
			}		
		}
		paint_y++;
		paint_x = 0;
	}
}

void	draw_map_player(t_data *data) // рисует игрока
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

void	draw_map_grid(t_data *data) // рисует сетку мини карты 
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
		i++;
		y = 0;
		x = 0;
		// printf("%d\n", i);
	}
}

void	draw_map_dir(t_data *data)
{
	t_vector dir;

	dir = init_vector(MAP_TILE_SIZE * cos(data->play.rad), \
			MAP_TILE_SIZE * cos(to_radiants(90) - data->play.rad));
	line_dda(data->map.img, data->map.img->width / 2, data->map.img->height / 2, \
			data->map.img->width / 2 + dir.x, data->map.img->height / 2 + dir.y);
}

void	mini_map(t_data *data, char **map) // рисует полностью мини карту 
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
	// рисует стены 
	while (map[j] != NULL)
	{
		if (j >= data->play.map.y - 4
			&& j <= data->play.map.y + 4)
		{
			while (map[j][i] != '\0')
			{
				if (i >= data->play.map.x - 4
					&& i <= data->play.map.x + 4)
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
	draw_map_dir(data);
}

void draw_everything(t_data *data) // вывод на экран
{
	mlx_put_image_to_window(data->mlx, data->win, data->skybox.img, data->sky_offset, 0);
	if (data->sky_offset > 0)
		mlx_put_image_to_window(data->mlx, data->win, data->skybox.img, data->sky_offset - data->skybox.width , 0);
	else if (data->sky_offset < WIDTH_WINDOW - data->skybox.width)
		mlx_put_image_to_window(data->mlx, data->win, data->skybox.img, data->sky_offset + data->skybox.width , 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->bg->img, 0, 0);
	// while (i < WIDTH_WINDOW)
	// {
	// 	line_dda(data->minimap.img, data->minimap.img->width / 2, data->minimap.img->height / 2,
	// 	data->minimap.img->width / 2 + data->rays[i].x_end - data->minimap.player.x,
	// 	data->minimap.img->height / 2 + data->rays[i].y_end - data->minimap.player.y);
	// 	i++;
	// }
	mlx_put_image_to_window(data->mlx, data->win, data->map.img->img, 20, 20);
	mlx_string_put(data->mlx, data->win, 60,
		data->map.img->height + 80, 0x0000FF00, ft_itoa(to_degrees(data->play.rad)));
	mlx_string_put(data->mlx, data->win, 90,
		data->map.img->height + 80, 0x00FFFF00, ft_itoa((data->play.rad)));
}
/*
// void	make_fog(int *color, float height)
// {
// 	int r;
// 	int g;
// 	int b;

// 	r = (((*color & 0x00FF0000) >> 16) + 350 / (int)height) << 16;
// 	g = (((*color & 0x0000FF00) >> 8) + 350 / (int)height) << 8;
// 	b = (*color & 0x000000FF) + 350 / (int)height;
// 	*color = r + g + b;
	// *color = *color + 10 * height;
// }

void	calculate_3d(t_data *data) // рисует 3d изображение 
{
	int x;
	int y;
	int color;
	float height;

	height = sqrt(data->rays[0].ray);
	x = 0;
	color = 0;
	y = HEIGTH_WINDOW / 2 - HEIGTH_WINDOW / height;
	while (x < WIDTH_WINDOW)
	{
		if (data->rays[x].type == 'W')
			color = 0x002b2b2b;
		else if (data->rays[x].type == 'E')
			color = 0x00595959;
		else if (data->rays[x].type == 'N')
			color = 0x005c4242;
		else if (data->rays[x].type == 'S')
			color = 0x00825f5f;
		// make_fog(&color, height);
		while (y < HEIGTH_WINDOW / 2 + HEIGTH_WINDOW / height)
		{
			if (y < HEIGTH_WINDOW && y > 0)
				my_mlx_pixel_put(data->bg, x, y, color);
			y++;
		}
		height = sqrt(data->rays[0].ray);
		y = HEIGTH_WINDOW / 2 - HEIGTH_WINDOW / height;
		x++;
	}
}
*/

void	raycasting(t_data *data) // вычисляет лчи  
{
	t_ray		ray;
	int		i;

	i = -1;
	calculate_off(data, &ray);
	ray.rad = data->play.rad - ((WIDTH_WINDOW / 2) * data->rad_del);
	while (++i < WIDTH_WINDOW)
	{
		calculate_ray(data, &ray);
		ray.rad += data->rad_del;
	}
	// int	i;
	// int j;

	// j = 0;
	// calculate_offset(data);
	// data->rays[j].rad = data->rad;
	// // if (cos(data->rad) == 0 || sin(data->rad) == 0)
	// // 	return ;
	// i =  WIDTH_WINDOW / 2;
	// while (i-- > - WIDTH_WINDOW / 2)
	// {
	// 	calculate_ray(data->minimap.x_off, data->minimap.y_off, data, &(data->rays[j]));
	// 	data->rays[j].rad = data->rad + to_radiants((double)i / 15);
	// 	i++;
	// 	j++;
	// }
}

void	calculate_off(t_data *data, t_ray *ray)
{
	data->play.off.x = data->play.pos.x - (data->play.map.x * MAP_TILE_SIZE);
	data->play.off.y = data->play.pos.y - (data->play.map.y * MAP_TILE_SIZE);
	if (data->play.rad > 0 && data->play.rad < M_PI)
		ray->delta.y = data->play.off.y;
	else
		ray->delta.y = MAP_TILE_SIZE - data->play.off.y;
	if (data->play.rad > M_PI / 2 && data->play.rad < (3 * M_PI) / 2)
		ray->delta.x = data->play.off.x;
	else
		ray->delta.x = MAP_TILE_SIZE - data->play.off.x;
}

void	calculate_ray(t_data *data, t_ray *ray)
{
	(void)data;
	(void)ray;
}

int	  raycast_loop(t_data	*data)
{
	mouse_action(data); // координаты мышки
	// raycasting(data); // высчитивает лучи
	floor_ceiling(data); // пол потолок
	// calculate_3d(data); // преобразует в 3d изображение
	mini_map(data, data->map.map); // алгоритм мини-карты
	// вывод изображения
	draw_everything(data); // вывод изображения
	return (0);
}
