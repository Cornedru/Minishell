/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 18:09:47 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_redirections(t_token **tokens, t_ast *node)
{
	t_redir	*redir;

	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if ((*tokens)->type == TOKEN_REDIR_IN
			|| (*tokens)->type == TOKEN_REDIR_OUT
			|| (*tokens)->type == TOKEN_REDIR_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC)
		{
			redir = parse_redir(tokens);
			if (redir)
				add_redir(&node->redirs, redir);
			else
			{
				free_ast(node);
				return ;
			}
		}
		else
			advance_token(tokens);
	}
}

static t_ast	*parse_simple_command(t_token **tokens)
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

static t_ast	*parse_command(t_token **tokens)
{
	if (!*tokens)
		return (NULL);
	return (parse_simple_command(tokens));
}

static t_ast	*create_pipeline_node(t_ast *left, t_ast *right)
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

static t_ast	*parse_pipeline(t_token **tokens)
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

static t_ast	*create_and_or_node(t_ast *left, t_ast *right, t_ast_type type)
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

static t_ast	*parse_and_or(t_token **tokens)
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

t_ast	*parse(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type == TOKEN_WORD && ft_strcmp((*tokens)->value,
			"clear") == 0)
	{
		ft_clear();
		free((*tokens)->value);
		return (parse_and_or(tokens));
	}
	return (parse_and_or(tokens));
}