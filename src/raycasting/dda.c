#include "cube.h"

// void line_dda(t_data_img *data, double x1, double y1, double x2, double y2)
// {
// 	// Целочисленные значения координат начала и конца отрезка,
// 	// округленные до ближайшего целого
// 	int iX1 = roundf(x1);
// 	int iY1 = roundf(y1);
// 	int iX2 = roundf(x2);
// 	int iY2 = roundf(y2);
// 	// Длина и высота линии
// 	int deltaX = abs(iX1 - iX2);
// 	int deltaY = abs(iY1 - iY2);
// 	// Считаем минимальное количество итераций, необходимое
// 	// для отрисовки отрезка. Выбирая максимум из длины и высоты
// 	// линии, обеспечиваем связность линии
// 	int length = deltaX;
// 	if (deltaX < deltaY)
// 		length = deltaY;
// 	// особый случай, на экране закрашивается ровно один пиксел
// 	if (length == 0)
// 	{
// 		my_mlx_pixel_put(data, iX1, iY1, 0x00000000);
// 		return;
// 	}
// 	// Вычисляем приращения на каждом шаге по осям абсцисс и ординат
// 	double dX = (x2 - x1) / length;
// 	double dY = (y2 - y1) / length;
// 	// Начальные значения
// 	double x = x1;
// 	double y = y1;
// 	// Основной цикл
// 	length++;
// 	while (length--)
// 	{
// 		x += dX;
// 		y += dY;
// 		my_mlx_pixel_put(data, roundf(x), roundf(y), 0x00000000);
// 	}
// }

void	prirashenie(t_data_img *data, t_vector *fir, t_vector *sec, int length)
{
	t_vector	d;
	t_vector	start;

	d.x = (sec->x - fir->x) / length;
	d.y = (sec->y - fir->y) / length;
	start.x = fir->x;
	start.y = fir->y;
	length++;
	while (length--)
	{
		start.x += d.x;
		start.y += d.y;
		my_mlx_pixel_put(data, roundf(start.x), roundf(start.y), 0x00FFFFFF);
	}
}

void	line_dda(t_data_img *data, t_vector fir, t_vector sec)
{
	int	delta_x;
	int	delta_y;
	int	length;

	delta_x = abs((int)roundf(fir.x) - (int)roundf(sec.x));
	delta_y = abs((int)roundf(fir.y) - (int)roundf(sec.y));
	length = delta_x;
	if (delta_x < delta_y)
		length = delta_y;
	if (length == 0)
	{
		my_mlx_pixel_put(data, roundf(fir.x), roundf(fir.y), 0x00FFFFFF);
		return ;
	}
	prirashenie(data, &fir, &sec, length);
}
