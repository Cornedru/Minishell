/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 02:53:07 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	char	**argv;
	int		argc;
	int		i;

	node = new_ast_node(AST_CMD);
	if (!node)
		return (NULL);
	argc = count_word_tokens(*tokens);
	if (argc == 0)
	{
		argv = (char **)gc_malloc(sizeof(char *) * 2);
		if (!argv)
		{
			free_ast(node);
			return (NULL);
		}
		argv[0] = gc_strdup("");
		argv[1] = NULL;
		node->args = argv;
		return (node);
	}
	argv = (char **)gc_malloc(sizeof(char *) * (argc + 1));
	if (!argv)
	{
		free_ast(node);
		return (NULL);
	}
	i = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			argv[i] = remove_quotes((*tokens)->value);
			if (!argv[i])
				argv[i] = gc_strdup((*tokens)->value);
			i++;
		}
		advance_token(tokens);
	}
	argv[i] = NULL;
	node->args = argv;
	return (node);
}

t_ast	*parse_command(t_token **tokens)
{
	if (!*tokens)
		return (NULL);
	return (parse_simple_command(tokens));
}

t_ast	*parse(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_and_or(tokens));
}
