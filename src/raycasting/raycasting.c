/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arman <arman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:22:22 by arman             #+#    #+#             */
/*   Updated: 2022/10/22 06:22:22 by arman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	line_dda(t_data_img *data, t_vector a, t_vector b)
{
	t_vector	delta;
	t_vector	cord;
	t_vector	d;
	int			length;

	delta = init_vector(fabsf(roundf(a.x) - roundf(b.x)), \
		fabsf(roundf(a.y) - roundf(b.y)));
	length = delta.x;
	if (delta.x < delta.y)
		length = delta.y;
	d = init_vector((b.x - a.x) / length, (b.y - a.y) / length);
	cord = init_vector(a.x, a.y);
	length++;
	while (length--)
	{
		cord.x += d.x;
		cord.y += d.y;
		if (cord.x > data->width || cord.y > data->height \
			|| cord.x < 0 || cord.y < 0)
			return ;
		my_mlx_pixel_put(data, roundf(cord.x), roundf(cord.y), 0x00000000);
	}
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
			my_mlx_pixel_put(data->bg, x++, y, data->c_color);
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

void	draw_everything(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->bg->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->map.img->img, 20, 20);
}

void	ver_line(t_data *data, int x, int draw_start, int draw_end)
{
	t_ray	*ray;
	int		tex_y;
	int		color;

	ray = &data->ray[x];
	while (draw_start <= draw_end)
	{
		tex_y = (int)ray->tex_pos % (SIZE_TEXTURE - 1);
		ray->tex_pos += ray->st;
		color = data->texture[(int)ray->flag_direction] \
			[(int)(SIZE_TEXTURE * tex_y + ray->tex_x)];
		my_mlx_pixel_put(data->bg, x, draw_start, color);
		draw_start++;
	}
}

void	calculate_3d(t_data *data, t_ray *ray, int x)
{
	int		draw_start;
	int		draw_end;

	ray->corner = M_PI / 2 - (ray->rad - data->play.rad);
	ray->perp_dist = ray->gipo * ft_sin(ray->corner);
	ray->line_height = (int)((HEIGTH_WINDOW / ray->perp_dist) * MAP_TILE_SIZE);
	draw_start = -ray->line_height / 2 + HEIGTH_WINDOW / 2;
	draw_end = ray->line_height / 2 + HEIGTH_WINDOW / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGTH_WINDOW)
		draw_end = HEIGTH_WINDOW - 1;
	ray->tex_x = (ray->wall_x / MAP_TILE_SIZE) * SIZE_TEXTURE;
	ray->st = 1.0 * SIZE_TEXTURE / ray->line_height;
	ray->tex_pos = (draw_start - HEIGTH_WINDOW \
		/ 2 + ray->line_height / 2) * ray->st;
	ver_line(data, x, draw_start, draw_end);
}
