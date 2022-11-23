/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arman <arman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:49:25 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/10/22 06:09:27 by arman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ch;

	ch = (unsigned char *)s;
	while (n--)
	{
		if (*ch == (unsigned char)c)
			return (ch);
		ch++;
	}
	return (NULL);
}
