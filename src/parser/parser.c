/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/27 17:24:17 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*advance_token(t_token **tokens)
{
	if (*tokens)
		*tokens = (*tokens)->next;
	return (*tokens);
}

static t_ast	*new_ast_node(t_ast_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ast));
	node->type = type;
	return (node);
}

static int	count_word_tokens(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp && tmp->type == TOKEN_WORD)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	**tokens_to_argv(t_token **tokens)
{
	int		count;
	char	**argv;
	int		i;

	count = count_word_tokens(*tokens);
	if (count == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < count && (*tokens) && (*tokens)->type == TOKEN_WORD)
	{
		argv[i] = ft_strdup((*tokens)->value);
		if (!argv[i])
		{
			ft_free_split(argv);
			return (NULL);
		}
		advance_token(tokens);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static t_redir	*parse_redir(t_token **tokens)
{
	t_redir		*redir;
	t_token_type	type;

	if (!*tokens || ((*tokens)->type != TOKEN_REDIR_IN &&
		(*tokens)->type != TOKEN_REDIR_OUT &&
		(*tokens)->type != TOKEN_REDIR_APPEND &&
		(*tokens)->type != TOKEN_HEREDOC))
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	type = (*tokens)->type;
	advance_token(tokens);
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		free(redir);
		return (NULL);
	}
	redir->type = type;
	redir->file = ft_strdup((*tokens)->value);
	redir->next = NULL;
	advance_token(tokens);
	return (redir);
}

static void	add_redir(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*current;

	if (!*redirs)
	{
		*redirs = new_redir;
		return;
	}
	current = *redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

static t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	t_redir	*redir;

	node = new_ast_node(AST_COMMAND);
	if (!node)
		return (NULL);
	node->redirs = NULL;
	while (*tokens && ((*tokens)->type == TOKEN_WORD ||
		(*tokens)->type == TOKEN_REDIR_IN ||
		(*tokens)->type == TOKEN_REDIR_OUT ||
		(*tokens)->type == TOKEN_REDIR_APPEND ||
		(*tokens)->type == TOKEN_HEREDOC))
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			if (!node->argv)
				node->argv = tokens_to_argv(tokens);
			else
				break;
		}
		else
		{
			redir = parse_redir(tokens);
			if (redir)
				add_redir(&node->redirs, redir);
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

static t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*pipeline;

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

static t_ast	*parse_and_or(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;
	t_ast_type	type;

	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	if (!*tokens || ((*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR))
		return (left);
	type = ((*tokens)->type == TOKEN_AND) ? AST_AND : AST_OR;
	advance_token(tokens);
	right = parse_and_or(tokens);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
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
void	ft_clear(void)
{
	write(1, "\033[H\033[2J", 7);
}

t_ast	*parse(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if (ft_strcmp((*tokens)->value, "clear") == 0)
	{
		ft_clear();
		free((*tokens)->value);
	}
	return (parse_and_or(tokens));
}

