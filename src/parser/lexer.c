/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/30 02:03:49 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//  int	handle_quotes(char *input, int i, char quote)
// {
// 	i++;
// 	while (input[i] && input[i] != quote)
// 		i++;
// 	if (input[i] == quote)
// 		i++;
// 	return (i);
// }

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
	else if (input[i] == '&' && input[i + 1] == '&')
		return (TOKEN_AND);
	return (TOKEN_WORD);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	t_token	*new_token;
	char	*value;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
		{
			i = extract_operator(input, i, &value);
			new_token = create_token(get_operator_type(value, 0), value);
		}
		else
		{
			i = extract_word_with_quotes(input, i, &value);
			new_token = create_token(TOKEN_WORD, value);
		}
		if (!new_token)
		{
			free(value);
			free_tokens(tokens);
			return (NULL);
		}
		add_token(&tokens, new_token);
		free(value);
	}
	return (tokens);
}
