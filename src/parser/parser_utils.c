/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 22:56:34 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

int	extract_word_with_quotes(char *input, int i, char **word)
{
	int		start;
	int		end;
	char	quote;

	start = i;
	end = i;
	while (input[end] && !is_operator(input[end]) && input[end] != ' '
		&& input[end] != '\t')
	{
		if (input[end] == '\'' || input[end] == '"')
		{
			quote = input[end];
			end++;
			while (input[end] && input[end] != quote)
				end++;
			if (input[end] == quote)
				end++;
		}
		else
		{
			end++;
		}
	}
	*word = ft_substr(input, start, end - start);
	return (end);
}

int	extract_operator(char *input, int i, char **op)
{
	int	len;

	len = get_operator_len(input, i);
	*op = ft_substr(input, i, len);
	return (i + len);
}

int	get_operator_len(char *input, int i)
{
	if ((input[i] == '|' && input[i + 1] == '|') || (input[i] == '<' && input[i
				+ 1] == '<') || (input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '&' && input[i + 1] == '&'))
		return (2);
	return (1);
}
