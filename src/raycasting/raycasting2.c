#include "cube.h"

t_vector	creat_vec(double x, double y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

// void	load_img(t_data *data, unsigned int *texture, char *path)
// {
// 	t_data_img	img;
// 	int			x;
// 	int			y;

// 	y = 0;
// 	img.img = mlx_xpm_file_to_image(data->mlx, path, &img.width, &img.height);
// 	img.addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	printf("asda\n");
// 	while (y < img.height)
// 	{
// 		x = 0;
// 		while (x < img.width)
// 		{
// 			texture[img.width * y + x] = img.addr[img.width * y + x];
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_destroy_image(data->mlx, img.img);
// }

// void	algoritm(t_data *data)
// {

// }

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

void	raycasting(t_data *data, t_cub *cub)
{
	cub->x = -1;

	for(int x = 0; x < texWidth; x++)
	{
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			cub->textur[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			cub->textur[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			cub->textur[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			cub->textur[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			cub->textur[4][texWidth * y + x] = 256 * xorcolor; //xor green
			cub->textur[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			cub->textur[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			cub->textur[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}
	while (++cub->x < WIDTH_WINDOW)
	{
		cub->camera_x = 2 * cub->x / (double)WIDTH_WINDOW - 1;
		cub->ray_dir.x = data->play.dir.x + data->play.plane.x * cub->camera_x;
		cub->ray_dir.y = data->play.dir.y + data->play.plane.y * cub->camera_x;
		cub->map_x = roundf(data->play.pos.x);
		cub->map_y = roundf(data->play.pos.y);
		cub->delta_d.x = (cub->ray_dir.x == 0) ? 1e30 : abs((int)(1 / cub->ray_dir.x));
		cub->delta_d.y = (cub->ray_dir.y == 0) ? 1e30 : abs((int)(1 / cub->ray_dir.y));
		cub->hit = 0;
		//calculate step and initial sideDist
		if(cub->ray_dir.x < 0)
		{
			cub->step_x = -1;
			cub->side_d.x = (data->play.pos.x - cub->map_x) * cub->delta_d.x;
		}
		else
		{
			cub->step_x = 1;
			cub->side_d.x = (cub->map_x + 1.0 - data->play.pos.x) * cub->delta_d.x;
		}
		if(cub->ray_dir.y < 0)
		{
			cub->step_y = -1;
			cub->side_d.y = (data->play.pos.y - cub->map_y) * cub->delta_d.y;
		}
		else
		{
			cub->step_y = 1;
			cub->side_d.y = (cub->map_y + 1.0 - data->play.pos.y) * cub->delta_d.y;
		}
		//perform DDA
		while (cub->hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(cub->side_d.x < cub->side_d.y)
			{
				cub->side_d.x += cub->delta_d.x;
				cub->map_x += cub->step_x;
				cub->side = 0;
			}
			else
			{
				cub->side_d.y += cub->delta_d.y;
				cub->map_y += cub->step_y;
				cub->side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[cub->map_x][cub->map_y] > 0)
				cub->hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (cub->side == 0)
			cub->perpwd = (cub->side_d.x - cub->delta_d.x);
		else
			cub->perpwd = (cub->side_d.y - cub->delta_d.y);

		//Calculate height of line to draw on screen
		cub->line_hight = (int)(HEIGTH_WINDOW / cub->perpwd);
		cub->pitch = 100;
		//calculate lowest and highest pixel to fill in current stripe
		cub->draw_start = -cub->line_hight / 2 + HEIGTH_WINDOW / 2 + cub->pitch;
		if(cub->draw_start < 0)
			cub->draw_start = 0;
		cub->draw_end = cub->line_hight / 2 + HEIGTH_WINDOW / 2 + cub->pitch;
		if(cub->draw_end >= HEIGTH_WINDOW)
			cub->draw_end = HEIGTH_WINDOW - 1;
		//texturing calculations
		cub->tex_num = worldMap[cub->map_x][cub->map_y] - 1; //1 subtracted from it so that texture 0 can be used!
		//calculate value of wallX
		if (cub->side == 0)
			cub->wall_x = data->play.pos.y + cub->perpwd * cub->ray_dir.y;
		else
			cub->wall_x = data->play.pos.x + cub->perpwd * cub->ray_dir.x;
		cub->wall_x -= floor(cub->wall_x);
		//x coordinate on the texture
		cub->tex_x = (int)roundf(cub->wall_x * (double)texWidth);
		if (cub->side == 0 && cub->ray_dir.x > 0)
			cub->tex_x = texWidth - cub->tex_x - 1;
		if (cub->side == 1 && cub->ray_dir.y < 0)
			cub->tex_x = texWidth - cub->tex_x - 1;
		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		cub->step = 1.0 * texHeight / cub->line_hight;
		// Starting texture coordinate
		cub->tex_pos = (cub->draw_start - cub->pitch - HEIGTH_WINDOW / 2 + cub->line_hight / 2) * cub->step;
		cub->y = cub->draw_start;
		while (cub->y++ < cub->draw_end)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			cub->tex_y = (int)cub->tex_pos & (texHeight - 1);
			cub->tex_pos += cub->step;
			cub->color = cub->textur[cub->tex_num][texHeight * cub->tex_y + cub->tex_x];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (cub->side == 1)
				cub->color = (cub->color >> 1) & 8355711;
			cub->buffer[cub->y][cub->x] = cub->color;
		}
	}
}
