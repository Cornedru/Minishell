/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/06 06:06:57 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_operator_token(char *input, int i, char **value,
		t_token_type *type)
{
	i = extract_operator(input, i, value);
	if (!*value)
		return (-1);
	*type = get_operator_type(*value, 0);
	if (*type == TOKEN_INVALID)
	{
		gc_free(*value);
		return (-1);
	}
	return (i);
}

static int	handle_word_token(char *input, int i, char **value,
		t_token_type *type)
{
	i = extract_word_with_quotes(input, i, value);
	if (!*value)
		return (-1);
	*type = TOKEN_WORD;
	return (i);
}

static int	add_new_token(t_token **tokens, char *value, t_token_type type)
{
	t_token	*new;

	new = create_token(type, value);
	if (!new)
	{
		gc_free(value);
		free_tokens(*tokens);
		*tokens = NULL;
		return (-1);
	}
	add_token(tokens, new);
	gc_free(value);
	return (0);
}

static int	process_token(char *input, int i, t_token **tokens)
{
	char			*value;
	t_token_type	type;
	int				res;

	if (is_operator(input[i]))
		res = handle_operator_token(input, i, &value, &type);
	else
		res = handle_word_token(input, i, &value, &type);
	if (res == -1)
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return (-1);
	}
	if (add_new_token(tokens, value, type) == -1)
		return (-1);
	return (res);
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
