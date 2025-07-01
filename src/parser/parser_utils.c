/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 18:09:55 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word_tokens(t_token *start)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = start;
	while (tmp && tmp->type != TOKEN_PIPE && tmp->type != TOKEN_AND
		&& tmp->type != TOKEN_OR)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	**allocate_argv(int count)
{
	char	**argv;

	if (count == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	return (argv);
}

static void	fill_argv(t_token **tokens, char **argv)
{
	int		i;
	char	*clean_str;

	i = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			clean_str = remove_quotes((*tokens)->value);
			if (!clean_str)
				clean_str = ft_strdup((*tokens)->value);
			argv[i++] = clean_str;
		}
		advance_token(tokens);
	}
	argv[i] = NULL;
}

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
		clean_file = ft_strdup((*tokens)->value);
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