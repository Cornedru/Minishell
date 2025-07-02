/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_addback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:00:26 by pespana           #+#    #+#             */
/*   Updated: 2025/07/02 18:10:14 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gc.h"
void	gc_addback(t_gc_leaf **gc, t_gc_leaf *new)
{
	t_gc_leaf	*tmp;

	if (!gc || !new)
		return ;
	new->next = NULL;
	if (!*gc)
	{
		*gc = new;
		return ;
	}
	tmp = *gc;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
