/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 22:57:19 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**gather_all_words(t_token **tokens)
{
	t_token	*start;
	int		count;
	char	**argv;

	start = *tokens;
	count = count_word_tokens(start);
	argv = allocate_argv(count);
	if (!argv)
		return (NULL);
	fill_argv(tokens, argv);
	return (argv);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	t_token	*start;

	node = new_ast_node(AST_COMMAND);
	if (!node)
		return (NULL);
	node->redirs = NULL;
	node->argv = NULL;
	start = *tokens;
	parse_redirections(tokens, node);
	*tokens = start;
	node->argv = gather_all_words(tokens);
	if (!node->argv && node->redirs)
	{
		node->argv = malloc(sizeof(char *) * 2);
		if (node->argv)
		{
			node->argv[0] = ft_strdup("");
			node->argv[1] = NULL;
		}
	}
	if (!node->argv)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}

t_ast	*parse_command(t_token **tokens)
{
	if (!*tokens)
		return (NULL);
	return (parse_simple_command(tokens));
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

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_command(tokens);
	if (!left)
		return (NULL);
	if (!*tokens || (*tokens)->type != TOKEN_PIPE)
		return (left);
	advance_token(tokens);
	right = parse_pipeline(tokens);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	return (create_pipeline_node(left, right));
}
