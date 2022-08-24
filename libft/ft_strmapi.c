/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:09:31 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/20 11:12:09 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ch;
	size_t	i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	ch = (char *)ft_calloc(i + 1, sizeof(char));
	if (!ch)
		return (0);
	i = 0;
	while (s[i])
	{
		ch[i] = f(i, s[i]);
		i++;
	}
	return (ch);
}
