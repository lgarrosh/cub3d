/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:41:37 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/14 20:42:54 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*ch;
	unsigned char	c1;
	int				i;

	ch = (char *)s;
	c1 = c;
	i = ft_strlen(ch);
	while (i >= 0)
	{
		if (ch[i] == c1)
			return (&ch[i]);
		i--;
	}
	return (NULL);
}
