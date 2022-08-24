/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:08:54 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/13 16:13:56 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ch;
	unsigned char	*ch1;
	int				i;

	i = 0;
	ch = (unsigned char *)s1;
	ch1 = (unsigned char *)s2;
	while (i < (int)n)
	{
		if (ch[i] != ch1[i])
			return (ch[i] - ch1[i]);
		i++;
	}
	return (0);
}
