/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/02 00:01:45 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

int	has_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	should_split_token(char *original, char *expanded)
{
	if (!has_quotes(original))
		return (0);
	return (has_whitespace(expanded));
}

t_ast	*create_pipeline_node(t_ast *left, t_ast *right)
{
	t_ast	*pipeline;

	pipeline = new_ast_node(AST_PIPELINE);
	if (!pipeline)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	pipeline->left = left;
	pipeline->right = right;
	return (pipeline);
}
