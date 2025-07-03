/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 06:10:24 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_ast	*new_ast_node(t_ast_type type)
// {
// 	t_ast	*node;

// 	node = (t_ast *)gc_malloc(sizeof(t_ast));
// 	if (!node)
// 		return (NULL);
// 	ft_bzero(node, sizeof(t_ast));
// 	node->type = type;
// 	return (node);
// }

// t_token	*advance_token(t_token **tokens)
// {
// 	if (*tokens)
// 		*tokens = (*tokens)->next;
// 	return (*tokens);
// }

// t_ast	*create_pipeline_node(t_ast *left, t_ast *right)
// {
// 	t_ast	*pipeline;

// 	pipeline = new_ast_node(AST_PIPE);
// 	if (!pipeline)
// 	{
// 		free_ast(left);
// 		free_ast(right);
// 		return (NULL);
// 	}
// 	pipeline->left = left;
// 	pipeline->right = right;
// 	return (pipeline);
// }

// t_ast	*create_and_or_node(t_ast *left, t_ast *right, t_ast_type type)
// {
// 	t_ast	*node;

// 	node = new_ast_node(type);
// 	if (!node)
// 	{
// 		free_ast(left);
// 		free_ast(right);
// 		return (NULL);
// 	}
// 	node->left = left;
// 	node->right = right;
// 	return (node);
// }
