/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:03:49 by preed             #+#    #+#             */
/*   Updated: 2022/09/14 15:53:56 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int save_wall_texture(char *line, t_data *data, int i)
{
	int		j;
	char	*path;

	j = 3;
	while (!ft_isprint(line[j]))
		j++;
	path = ft_strdup(&line[j]);
	data->walls[i].img = mlx_xpm_file_to_image(data->mlx, path,
											   &data->walls[i].width, &data->walls[i].height);
	if (!data->walls[i].img)
		return (0);
	return (0);
}

int save_color(char *line, t_data *data, char f_or_c)
{
	char	rgb[3][4];
	int		j;
	int		k;
	int		i;

	j = 0;
	i = 2;
	k = 0;
	while (line[i] && j <= 2)
	{
		while (!ft_isprint(line[i]))
			i++;
		if (!ft_isdigit(line[i]))
			return (1);
		while (ft_isdigit(line[i]) && k <= 2)
			rgb[j][k++] = line[i++];
		while (k <= 2)
			rgb[j][k++] = '.';
		rgb[j][k] = '\0';
		j++;
		k = 0;
		if (line[i] == ',' || line[i] == '\0')
			i++;
		else
			return (1);
	}
	if (f_or_c == 'F')
		data->f_color = string_to_rgb((char *)rgb);
	else
		data->c_color = string_to_rgb((char *)rgb);
	return (0);
}

int check_and_save_data(char **info, t_data *data)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (info[i])
	{
		if (!ft_strncmp(info[i], "NO ", 3))
			ret = save_wall_texture(info[i], data, 0);
		else if (!ft_strncmp(info[i], "SO ", 3))
			ret = save_wall_texture(info[i], data, 1);
		else if (!ft_strncmp(info[i], "WE ", 3))
			ret = save_wall_texture(info[i], data, 2);
		else if (!ft_strncmp(info[i], "EA ", 3))
			ret = save_wall_texture(info[i], data, 3);
		else if (!ft_strncmp(info[i], "F ", 2))
			ret = save_color(info[i], data, 'F');
		else if (!ft_strncmp(info[i], "C ", 2))
			ret = save_color(info[i], data, 'C');
		else
			return (1);
		if (ret)
			return (ret);
		i++;
	}
	return (0);
}

int check_map(char *string, t_data *data)
{
	int i;
	int j;
	int line_length;
	char **info;

	j = 0;
	info = ft_calloc(7, sizeof(char *));
	i = 0;
	line_length = 0;
	while (j != 6 && string[i] != '\0')
	{
		while (string[i] != '\n')
		{
			line_length++;
			i++;
		}
		if (line_length)
		{
			info[j] = ft_calloc(line_length + 1, sizeof(char *));
			ft_memcpy(info[j], &string[i - line_length], line_length);
			line_length = 0;
			j++;
		}
		i++;
	}
	if (j != 6 || check_and_save_data(info, data))
		return (1);
	while (string[i] == '\n')
		i++;
	if (save_map(string, i, data))
		return (1);
	return (0);
}

void save_to_string(char **string, char *buf, int fd)
{
	char *save;

	save = ft_strjoin(*string, buf);
	free(*string);
	*string = save;
	if (save == NULL)
		close(fd);
}

char *read_file(int fd)
{
	char buf[1024];
	int ret;
	char *string;

	string = ft_calloc(1, 1);
	if (string == NULL)
		return (NULL);
	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, buf, 1024);
		if (ret == -1)
		{
			free(string);
			close(fd);
			return (NULL);
		}
		else
		{
			buf[ret] = '\0';
			save_to_string(&string, buf, fd);
		}
	}
	return (string);
}

int open_file(char *filename, t_data *data)
{
	int fd;
	char *string;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf("ERROR: Could not read the file!\n"));
	string = read_file(fd);
	if (string == NULL)
		return (printf("ERROR: File reading failed!\n"));
	close(fd);
	if (check_map(string, data))
		return (printf("ERROR: Map file not valid!\n"));
	return (0);
}

int parser(int argc, char *argv[], t_data *data)
{
	if (argc != 2)
		return (printf("ERROR: Wrong number of args!\n"));
	if (open_file(argv[1], data))
		return (1);
	return (0);
}