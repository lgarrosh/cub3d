/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:51:06 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/27 16:01:06 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_quantity(const char *ch, char c)
{
	int		i;
	size_t	len;

	len = 0;
	i = 0;
	while (ch[i])
	{
		if ((ch[i] != c) && (ch[i + 1] == c || ch[i + 1] == '\0'))
			len++;
		i++;
	}
	return (len);
}

static char	*ft_creat(const char *ch, char c, size_t t)
{
	int		i;
	size_t	len;
	char	*c1;

	i = 0;
	while (t)
	{
		len = 0;
		while (ch[i] == c)
			i++;
		while (ch[len + i] != c && ch[len + i] != 0)
			len++;
		if (t == 1)
			c1 = ft_substr(ch, i, len);
		i += len;
		t--;
	}
	return (c1);
}

static void	ft_free(char **ch)
{
	int	i;

	i = 0;
	while (ch[i] != 0)
	{
		free(ch[i]);
		i++;
	}
	free(ch);
}

char	**ft_split(char const *s, char c)
{
	char	**ch;
	size_t	qu;
	size_t	i;

	if (s == 0)
		return (0);
	i = 0;
	qu = ft_quantity(s, c);
	ch = (char **)ft_calloc(qu + 1, sizeof(char *));
	if (!ch)
		return (0);
	while (i < qu)
	{
		ch[i] = ft_creat(s, c, i + 1);
		if (!ch[i])
		{
			ft_free(ch);
			return (0);
		}
		i++;
	}
	return (ch);
}
