/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:00:22 by pespana           #+#    #+#             */
/*   Updated: 2025/07/02 18:10:17 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gc.h"
void	gc_delone(t_gc_leaf *gc)
{
	if (!gc)
		return ;
	ft_free(gc->data);
	ft_free(gc);
}

void	gc_clear(t_gc_leaf **gc)
{
	t_gc_leaf	*tmp;

	if (!gc || !*gc)
		return ;
	while (*gc)
	{
		tmp = (*gc)->next;
		gc_delone(*gc);
		*gc = tmp;
	}
}
