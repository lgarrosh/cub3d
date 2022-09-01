/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:02:45 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/09/01 17:02:46 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_error(int fd, char *error, int ret)
{
	if (write(fd, error, ft_strlen(error)) > 0)
		return (ret);
	return(-1);
}