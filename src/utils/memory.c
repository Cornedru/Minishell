/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 02:47:15 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		gc_free(tokens->value);
		gc_free(tokens);
		tokens = tmp;
	}
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->args)
		gc_free_array((void **)ast->args);
	if (ast->filename)
		gc_free(ast->filename);
	free_ast(ast->left);
	free_ast(ast->right);
	gc_free(ast);
}

int	count_word_tokens(t_token *start)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = start;
	while (tmp && tmp->type != TOKEN_PIPE && tmp->type != TOKEN_AND
		&& tmp->type != TOKEN_OR)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}