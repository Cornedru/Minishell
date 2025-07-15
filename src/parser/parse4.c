/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/15 02:44:39 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	get_operator_type(char *input, int i)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			return (TOKEN_OR);
		return (TOKEN_PIPE);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (TOKEN_REDIR_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	else if (input[i] == '&')
	{
		if (input[i + 1] == '&')
			return (TOKEN_AND);
		return (TOKEN_INVALID);
	}
	return (TOKEN_WORD);
}

int	are_quotes_closed(const char *str)
{
	int	i;
	int	single;
	int	doubleq;

	i = 0;
	single = 0;
	doubleq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && doubleq % 2 == 0)
			single++;
		else if (str[i] == '"' && single % 2 == 0)
			doubleq++;
		i++;
	}
	if (single % 2 == 0 && doubleq % 2 == 0)
		return (1);
	return (0);
}

char	*expand_variable(char *str, int *i, t_sys *sys)
{
	char	*res;
	int		start;

	res = expand_special_var(str, i, sys);
	if (res)
		return (res);
	res = handle_invalid_or_numeric_var(str, i);
	if (res)
		return (res);
	start = *i + 1;
	return (extract_env_value(str, i, start, sys));
}

int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = tokens;
	if (curr && is_operator_token(curr->type))
		return (check_operator_syntax(curr, prev));
	while (curr)
	{
		if (is_redirection_token(curr->type))
		{
			if (!check_redirection_syntax(curr))
				return (0);
		}
		else if (is_operator_token(curr->type))
		{
			if (!check_operator_syntax(curr, prev))
				return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}
