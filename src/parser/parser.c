/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 22:57:27 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redirections(t_token **tokens, t_ast *node)
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

void	fill_argv(t_token **tokens, char **argv)
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

int	count_word_tokens(t_token *start)
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

char	**allocate_argv(int count)
{
	char	**argv;

	if (count == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	return (argv);
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
