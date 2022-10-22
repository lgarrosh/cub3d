/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:40:42 by arman             #+#    #+#             */
/*   Updated: 2022/10/22 21:48:37 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_error(int fd, char *error, int ret)
{
	if (write(fd, error, ft_strlen(error)) > 0)
		return (ret);
	return (-1);
}
