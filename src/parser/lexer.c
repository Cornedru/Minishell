/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 05:08:28 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

static int	skip_whitespace(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

// static int	handle_quotes(char *input, int i, char quote)
// {
// 	i++;
// 	while (input[i] && input[i] != quote)
// 		i++;
// 	if (input[i] == quote)
// 		i++;
// 	return (i);
// }

static t_token_type	get_operator_type(char *input, int i)
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

static int	get_operator_len(char *input, int i)
{
	if ((input[i] == '|' && input[i + 1] == '|') ||
		(input[i] == '<' && input[i + 1] == '<') ||
		(input[i] == '>' && input[i + 1] == '>') ||
		(input[i] == '&' && input[i + 1] == '&'))
		return (2);
	return (1);
}

static t_token	*create_token(t_token_type type, char *value)
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

static void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new_token;
		return;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

static int	extract_word_with_quotes(char *input, int i, char **word)
{
	int	start;
	int	end;

	start = i;
	end = i;
	
	// Continue until we hit whitespace or operator
	while (input[end] && !is_operator(input[end]) && 
		   input[end] != ' ' && input[end] != '\t')
	{
		if (input[end] == '\'' || input[end] == '"')
		{
			// Handle quoted sections
			char quote = input[end];
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

static int	extract_operator(char *input, int i, char **op)
{
	int	len;

	len = get_operator_len(input, i);
	*op = ft_substr(input, i, len);
	return (i + len);
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
			break;
			
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