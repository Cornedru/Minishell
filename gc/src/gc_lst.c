/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 02:26:42 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/29 02:27:46 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

void	gc_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->content);
		gc_free((void *)lst);
	}
}

void	gc_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		gc_lstdelone(*lst, del);
		*lst = tmp;
	}
	lst = NULL;
}
