/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:18:01 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/13 16:18:05 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*ch1;
	unsigned char	ch;

	ch1 = b;
	ch = (unsigned char)c;
	while (len--)
	{
		*ch1 = ch;
		ch1++;
	}
	return (b);
}
