/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:48:12 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/25 16:48:13 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*l;
	t_list	*next;

	l = 0;
	if (!lst || !f)
		return (l);
	map = lst->next;
	l = ft_lstnew((*f)(lst->content));
	if (!l)
		return (NULL);
	while (map)
	{
		next = ft_lstnew((*f)(map->content));
		if (!next)
		{
			ft_lstclear(&l, del);
			return (NULL);
		}
		ft_lstadd_back(&l, next);
		map = map->next;
	}
	return (l);
}
