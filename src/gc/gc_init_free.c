/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:58:24 by pespana           #+#    #+#             */
/*   Updated: 2025/06/27 03:02:57 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_branch(t_gc *gc, int id)
{
	t_gc	*tmp;

	while (gc != NULL)
	{
		tmp = gc->next;
		if (gc->id == id)
		{
			gc_clear(&(gc->leaf));
		}
		gc = tmp;
	}
}

void	free_exit(t_gc *gc)
{
	t_gc	*tmp;

	while (gc != NULL)
	{
		tmp = gc->next;
		gc_clear(&(gc->leaf));
		ft_free(gc);
		gc = tmp;
	}
	rl_clear_history();
	exit(0);
}

void	gc_cleanup_all(t_gc *gc)
{
	t_gc	*tmp;

	while (gc != NULL)
	{
		tmp = gc->next;
		gc_clear(&(gc->leaf));
		ft_free(gc);
		gc = tmp;
	}
}

void	init_gc(t_gc **gc)
{
	int		i;
	t_gc	*current;
	t_gc	*prev;

	current = NULL;
	prev = NULL;
	i = 0;
	while (i < 3)
	{
		current = malloc(sizeof(t_gc));
		if (!current)
			free_exit(*gc);
		ft_memset(current, 0, sizeof(t_gc));
		current->id = i;
		if (prev == NULL)
			*gc = current;
		else
			prev->next = current;
		prev = current;
		current = current->next;
		i++;
	}
}
