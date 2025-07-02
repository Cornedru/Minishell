/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:00:22 by pespana           #+#    #+#             */
/*   Updated: 2025/06/26 22:09:49 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
