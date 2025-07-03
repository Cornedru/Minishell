/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 07:36:01 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// t_token_type	get_operator_type(char *input, int i)
// {
// 	if (input[i] == '|')
// 	{
// 		if (input[i + 1] == '|')
// 			return (TOKEN_OR);
// 		return (TOKEN_PIPE);
// 	}
// 	else if (input[i] == '<')
// 	{
// 		if (input[i + 1] == '<')
// 			return (TOKEN_HEREDOC);
// 		return (TOKEN_REDIR_IN);
// 	}
// 	else if (input[i] == '>')
// 	{
// 		if (input[i + 1] == '>')
// 			return (TOKEN_REDIR_APPEND);
// 		return (TOKEN_REDIR_OUT);
// 	}
// 	else if (input[i] == '&' && input[i + 1] == '&')
// 		return (TOKEN_AND);
// 	return (TOKEN_WORD);
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
	else if (input[i] == '&')
	{
		if (input[i + 1] == '&')
			return (TOKEN_AND);
		return (TOKEN_INVALID); // opérateur seul invalide
	}
	return (TOKEN_WORD); // fallback
}

// static int	process_token(char *input, int i, t_token **tokens)
// {
// 	t_token	*new_token;
// 	char	*value;

// 	if (is_operator(input[i]))
// 	{
// 		i = extract_operator(input, i, &value);
// 		new_token = create_token(get_operator_type(value, 0), value);
// 	}
// 	else
// 	{
// 		i = extract_word_with_quotes(input, i, &value);
// 		new_token = create_token(TOKEN_WORD, value);
// 	}
// 	if (!new_token)
// 	{
// 		gc_free(value);
// 		free_tokens(*tokens);
// 		*tokens = NULL;
// 		return (-1);
// 	}
// 	add_token(tokens, new_token);
// 	gc_free(value);
// 	return (i);
// }

static int	process_token(char *input, int i, t_token **tokens)
{
	t_token		*new_token;
	char		*value;
	t_token_type	type;

	if (is_operator(input[i]))
	{
		i = extract_operator(input, i, &value);
		if (!value)
			return (-1);
		type = get_operator_type(value, 0);
		if (type == TOKEN_INVALID)
		{
			gc_free(value);
			free_tokens(*tokens);
			*tokens = NULL;
			return (-1);
		}
	}
	else
	{
		i = extract_word_with_quotes(input, i, &value);
		if (!value)
			return (-1);
		type = TOKEN_WORD;
	}

	new_token = create_token(type, value);
	if (!new_token)
	{
		gc_free(value);
		free_tokens(*tokens);
		*tokens = NULL;
		return (-1);
	}
	add_token(tokens, new_token);
	gc_free(value); // OK si value a été strdup dans create_token
	return (i);
}

int	are_quotes_closed(const char *str)
{
	int	single = 0;
	int	doubleq = 0;

	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '\'' && doubleq % 2 == 0)
			single++;
		else if (str[i] == '"' && single % 2 == 0)
			doubleq++;
	}
	return (single % 2 == 0 && doubleq % 2 == 0);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	int		result;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (!are_quotes_closed(input))
			return (NULL);
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		result = process_token(input, i, &tokens);
		if (result == -1)
			return (NULL);
		i = result;
	}
	return (tokens);
}
