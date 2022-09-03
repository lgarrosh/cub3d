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

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24


void	put_frime(t_data *data, int *time)
{
	mlx_put_image_to_window(data->mlx, data->win, data->raycast->img, 0, 0);
	mlx_string_put(data->mlx, data->win, WIDTH_WINDOW - 30,
		HEIGTH_WINDOW - 18, 0x00FFFFFF, ft_itoa(1000 / (time[1] - time[0])));
}

void	verLine(t_data *data, int x, int start, int end, int color)
{
	for (int y = start; y < end; y++)
	{
		my_mlx_pixel_put(data->raycast, x, y, color);
	}
	printf("%d %d %d %d\n", x, start, end, color);
}

void	raycasting(t_data *data)
{
	int worldMap[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	double		camera_x;
	int			x;
	int mapx;
	int mapy;

	x = 0;
	while (x <= WIDTH_WINDOW)
	{
		t_vector rayDir;
		camera_x = 2 * x / WIDTH_WINDOW - 1;
		rayDir.x = data->play.dir.x + data->play.plane.x * camera_x;
		rayDir.y = data->play.dir.y + data->play.plane.y * camera_x;

		mapx = round(data->play.pos.x);
		mapy = round(data->play.pos.y);

		t_vector sidedist;
		t_vector deltadist;

		deltadist.x = (rayDir.x == 0) ? 1e30 : fabs(1 / rayDir.x);
		deltadist.y = (rayDir.y == 0) ? 1e30 : fabs(1 / rayDir.y);

		double perpwalldist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if (rayDir.x < 0)
		{
			stepX = -1;
			sidedist.x = (data->play.pos.x - mapx) * deltadist.x;
		}
		else
		{
			stepX = 1;
			sidedist.x = (mapx + 1.0 - data->play.pos.x) * deltadist.x;
		}
		if (rayDir.y < 0)
		{
			stepY = -1;
			sidedist.y = (data->play.pos.y - mapy) * deltadist.y;
		}
		else
		{
			stepY = 1;
			sidedist.y = (mapy + 1.0 - data->play.pos.y) * deltadist.y;
		}
		while (hit == 0)
		{
			if(sidedist.x < sidedist.y)
			{
				sidedist.x += deltadist.x;
				mapx += stepX;
				side = 0;
			}
			else
			{
				sidedist.y += deltadist.y;
				mapy += stepY;
				side = 1;
			}
			if (worldMap[mapx][mapy] > 0) 
				hit = 1;
		}
		if (side == 0)
			perpwalldist = sidedist.x - deltadist.x;
		else
			perpwalldist = sidedist.y - deltadist.y;
		int lineHeight;
		lineHeight = round(HEIGTH_WINDOW / perpwalldist);
		int drawStart;
		drawStart = -lineHeight / 2 + HEIGTH_WINDOW / 2;
		if(drawStart < 0) 
			drawStart = 0;
		int drawEnd;
		drawEnd = lineHeight / 2 + HEIGTH_WINDOW / 2;
		if(drawEnd >= HEIGTH_WINDOW) 
			drawEnd = HEIGTH_WINDOW - 1;
		int color;
		switch(worldMap[mapx][mapy])
		{
			case 1:  color = create_trgb(0, 255, 0, 0);    break; //red
			case 2:  color = create_trgb(0, 0, 255, 0);  break; //green
			case 3:  color = create_trgb(0, 0, 0, 255);   break; //blue
			case 4:  color = create_trgb(0, 255, 255, 0);  break; //white
			default: color = create_trgb(0, 255, 0, 255); break; //yellow
		}
		if (side == 1) 
			color /= 2;
		verLine(data, x, drawStart, drawEnd, color);
		x++;
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

void	mini_map(t_data *data, char *map)
{
	int	x;
	int	y;
	// int	i;
	(void)map;

	x = 0;
	y = 0;
	while (y < data->minimap.img->height)
	{
		while (x < data->minimap.img->width)
			my_mlx_pixel_put(data->minimap.img, x++, y, 0xA0FFFFFF);
		x = 0;
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img->img, 20, 20);
}

int	raycast_loop(t_data	*data)
{
	int time[2] = {100000, 122330};
	// floor_ceiling(data);
	// mini_map(data, data->other.map);
	raycasting(data);
	put_frime(data, time);
	return (0);
}
