/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/02 00:01:25 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_empty_argv(void)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 2);
	if (argv)
	{
		argv[0] = ft_strdup("");
		argv[1] = NULL;
	}
	return (argv);
}

static int	init_command_node(t_ast **node)
{
	*node = new_ast_node(AST_COMMAND);
	if (!*node)
		return (0);
	(*node)->redirs = NULL;
	(*node)->argv = NULL;
	return (1);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	t_token	*start;

	if (!init_command_node(&node))
		return (NULL);
	start = *tokens;
	parse_redirections(tokens, node);
	*tokens = start;
	node->argv = gather_all_words(tokens);
	if (!node->argv && node->redirs)
		node->argv = create_empty_argv();
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
