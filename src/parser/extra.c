/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/26 23:52:34 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_consecutive_words(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type == TOKEN_WORD)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	char	**args;
	int		count;
	int		i;

	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (NULL);
	count = count_consecutive_words(*tokens);
	node = new_ast_node(AST_CMD);
	if (!node)
		return (NULL);
	args = (char **)gc_malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (free_ast(node), NULL);
	i = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD && i < count)
	{
		// args[i] = remove_quotes((*tokens)->value);
		if (!args[i])
			args[i] = gc_strdup((*tokens)->value);
		advance_token(tokens);
		i++;
	}
	args[i] = NULL;
	node->args = args;
	return (node);
}

t_ast	*collect_redirections_and_args(t_token **tokens, t_ast **cmd)
{
	t_ast	*redirs;
	t_ast	*last_redir;
	t_ast	*new_redir;
	char	**additional_args;

	additional_args = NULL;
	redirs = NULL;
	last_redir = NULL;
	*cmd = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if (is_redirection_token((*tokens)->type))
		{
			new_redir = parse_single_redirection(tokens);
			if (!new_redir)
			{
				free_ast(redirs);
				free_ast(*cmd);
				return (NULL);
			}
			if (!redirs)
				redirs = new_redir;
			else
			{
				last_redir = redirs;
				while (last_redir->left)
					last_redir = last_redir->left;
				last_redir->left = new_redir;
			}
		}
		else if ((*tokens)->type == TOKEN_WORD)
		{
			if (!*cmd)
			{
				*cmd = parse_simple_command(tokens);
				if (!*cmd)
				{
					free_ast(redirs);
					return (NULL);
				}
			}
			else
			{
				additional_args = gather_all_words(tokens);
				if (additional_args && additional_args[0])
				{
					(*cmd)->args = merge_args((*cmd)->args, additional_args);
					if (!(*cmd)->args)
					{
						free_ast(redirs);
						free_ast(*cmd);
						return (NULL);
					}
				}
			}
		}
		else
			break ;
	}
	return (redirs);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	skip_whitespace(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}
