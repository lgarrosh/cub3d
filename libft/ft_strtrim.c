/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:34:42 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/15 21:00:34 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_str(char c, const char *ch)
{
	int	i;

	i = 0;
	while (ch[i])
	{
		if (c == ch[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ch;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	end = 0;
	if (!s1 || !set)
		return (0);
	while (s1[start] && ft_char_in_str(s1[start], set))
		start++;
	if (s1[start] != '\0')
	{
		end = ft_strlen(s1);
		while (ft_char_in_str(s1[end - 1], set))
			end--;
		end = ft_strlen(s1) - end;
	}
	i = ft_strlen(s1) - start - end + 1;
	ch = (char *)ft_calloc(i, 1);
	if (!ch)
		return (0);
	ft_strlcpy(ch, &s1[start], i);
	return (ch);
}
