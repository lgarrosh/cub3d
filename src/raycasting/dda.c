#include "cube.h"

void line_dda(t_data *data, double x1, double y1, double x2, double y2)
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
		my_mlx_pixel_put(data->img, iX1, iY1, 0x00FFFFFF);
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
		my_mlx_pixel_put(data->img, roundf(x), roundf(y), 0x00FFFFFF);
	}
}

void    put_cell(t_data *data)
{
	int step = 50;

	for (int x = step; x <= WIDTH_WINDOW; x += step)
	{
		line_dda(data, x, 0, x, HEIGTH_WINDOW);
	}
	for (int y = step; y <= HEIGTH_WINDOW; y += step)
	{
		line_dda(data, 0, y, WIDTH_WINDOW, y);
	}
}
