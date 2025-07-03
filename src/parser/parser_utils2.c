/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 02:05:13 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redir	*create_redir(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

t_redir	*parse_redir(t_token **tokens)
{
	t_token_type	type;
	char			*clean_file;

	if (!*tokens || ((*tokens)->type != TOKEN_REDIR_IN
			&& (*tokens)->type != TOKEN_REDIR_OUT
			&& (*tokens)->type != TOKEN_REDIR_APPEND
			&& (*tokens)->type != TOKEN_HEREDOC))
		return (NULL);
	type = (*tokens)->type;
	advance_token(tokens);
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (NULL);
	clean_file = remove_quotes((*tokens)->value);
	if (!clean_file)
		clean_file = gc_strdup((*tokens)->value);
	advance_token(tokens);
	return (create_redir(type, clean_file));
}

void	add_redir(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*current;

	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	current = *redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

t_token	*advance_token(t_token **tokens)
{
	if (*tokens)
		*tokens = (*tokens)->next;
	return (*tokens);
}

t_ast	*new_ast_node(t_ast_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ast));
	node->type = type;
	return (node);
}
