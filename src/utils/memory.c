/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 00:56:14 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->argv)
		ft_free_split(ast->argv);
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
}

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "malloc error\n", 13);
		exit(1);
	}
	return (ptr);
}

char	*safe_strdup(const char *s)
{
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
	{
		write(2, "malloc error\n", 13);
		exit(1);
	}
	return (dup);
}