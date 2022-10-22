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

int	save_wall_texture(char *line, t_data *data, int i);

int	save_color_t(char *line, char rgb[3][4])
{
	int		j;
	int		k;
	int		i;

	j = -1;
	i = 2;
	k = 0;
	while (line[i] && ++j <= 2)
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
		k = 0;
		if (line[i] == ',' || line[i] == '\0')
			i++;
		else
			return (1);
	}
	return (0);
}

int	save_color(char *line, t_data *data, char f_or_c)
{
	char	rgb[3][4];

	if (save_color_t(line, rgb))
		return (1);
	if (f_or_c == 'F')
		data->f_color = string_to_rgb((char *)rgb);
	else
		data->c_color = string_to_rgb((char *)rgb);
	return (0);
}

int	check_and_save_data(char **info, t_data *data)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (info[++i])
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
	}
	return (0);
}

int	check_map_t(t_data *data, char *string, int i)
{
	while (string[i] == '\n')
		i++;
	if (save_map(string, i, data))
		return (1);
	return (0);
}

int	check_map(char *string, t_data *data)
{
	int		i;
	int		j;
	int		line_length;
	char	**info;

	j = 0;
	info = ft_calloc(7, sizeof(char *));
	i = -1;
	line_length = 0;
	while (j != 6 && string[++i] != '\0')
	{
		i--;
		while (string[++i] != '\n')
			line_length++;
		if (line_length)
		{
			info[j] = ft_calloc(line_length + 1, sizeof(char *));
			ft_memcpy(info[j++], &string[i - line_length], line_length);
			line_length = 0;
		}
	}
	if (j != 6 || check_and_save_data(info, data))
		return (1);
	return (check_map_t(data, string, i));
}
