/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 03:45:49 by pespana           #+#    #+#             */
/*   Updated: 2025/06/27 03:02:54 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_gc_leaf	*gc_lstnew(void *data)
{
	t_gc_leaf	*gc;

	if (!data)
		return (NULL);
	gc = malloc(sizeof(t_gc_leaf));
	if (!gc)
		return (NULL);
	gc->data = data;
	gc->next = NULL;
	return (gc);
}

void	*gc_malloc2(t_gc_leaf **leaf, size_t size)
{
	void		*ret;
	t_gc_leaf	*node;

	if (size < 1)
		return (NULL);
	ret = malloc(size);
	if (!ret)
		return (NULL);
	node = gc_lstnew(ret);
	if (!node)
		return (NULL);
	gc_addback(leaf, node);
	return (ret);
}

void	*gc_malloc(t_gc *gc, size_t size, int id)
{
	void	*ret;
	t_gc	*head;

	head = gc;
	while (id > 0)
	{
		gc = gc->next;
		id--;
	}
	ret = gc_malloc2(&(gc->leaf), size);
	if (!ret)
		free_exit(head);
	return (ret);
}
