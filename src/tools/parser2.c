/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arman <arman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:45:10 by arman             #+#    #+#             */
/*   Updated: 2022/10/22 07:43:01 by arman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		check_map(char *string, t_data *data);

void	save_to_string(char **string, char *buf, int fd)
{
	char	*save;

	save = ft_strjoin(*string, buf);
	free(*string);
	*string = save;
	if (save == NULL)
		close(fd);
}

char	*read_file(int fd)
{
	char	buf[1024];
	int		ret;
	char	*string;

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

int	open_file(char *filename, t_data *data)
{
	int		fd;
	char	*string;

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

int	parser(int argc, char *argv[], t_data *data)
{
	if (argc != 2)
		return (printf("ERROR: Wrong number of args!\n"));
	if (open_file(argv[1], data))
		return (1);
	return (0);
}
