/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:14:49 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/23 16:14:50 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*h;

	h = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (h->next != 0)
	{
		h = h->next;
	}
	h->next = new;
}
