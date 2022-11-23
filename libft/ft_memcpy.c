/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arman <arman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:20:02 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/10/22 06:09:35 by arman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t count)
{
	unsigned char	*ch;
	unsigned char	*ch1;
	int				i;

	if (!dest && !source)
		return (NULL);
	i = 0;
	ch = dest;
	ch1 = (unsigned char *)source;
	while (i < (int)count)
	{
		ch[i] = ch1[i];
		i++;
	}
	return (dest);
}
