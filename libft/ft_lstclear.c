/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:14:43 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/23 17:02:24 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*this;

	if (!(*lst) || !del)
		return ;
	while ((*lst)->next != 0)
	{
		this = (*lst)->next;
		ft_lstdelone(*lst, (*del));
		*lst = this;
	}
	ft_lstdelone(*lst, (*del));
	*lst = 0;
}
