/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/02 21:46:06 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_and_or_node(t_ast *left, t_ast *right, t_ast_type type)
{
	t_ast	*node;

	node = new_ast_node(type);
	if (!node)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse_and_or(t_token **tokens)
{
	t_ast		*left;
	t_ast		*right;
	t_ast_type	type;

	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	if (!*tokens || ((*tokens)->type != TOKEN_AND
			&& (*tokens)->type != TOKEN_OR))
		return (left);
	if ((*tokens)->type == TOKEN_AND)
		type = AST_AND;
	else
		type = AST_OR;
	advance_token(tokens);
	right = parse_and_or(tokens);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	return (create_and_or_node(left, right, type));
}
