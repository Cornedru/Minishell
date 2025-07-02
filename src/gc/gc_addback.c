/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_addback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:00:26 by pespana           #+#    #+#             */
/*   Updated: 2025/06/03 03:38:48 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
