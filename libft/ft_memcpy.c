/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:20:02 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/13 16:30:06 by lgarrosh         ###   ########.fr       */
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
