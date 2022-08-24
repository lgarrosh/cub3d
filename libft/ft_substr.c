/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:50:57 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/15 18:23:30 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ch;
	size_t	max_len;

	if (s == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		max_len = 0;
	else
	{
		max_len = ft_strlen(s) - start;
		if (max_len > len)
			max_len = len;
	}
	ch = (char *)malloc(max_len + 1);
	if (!ch)
		return (NULL);
	ft_strlcpy(ch, &s[start], max_len + 1);
	return (ch);
}
