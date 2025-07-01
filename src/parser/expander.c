/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 18:47:22 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_special_var(char *str, int *i, t_shell *shell)
{
	int	start;

	start = *i + 1;
	if (str[start] == '?')
	{
		*i = start + 1;
		return (ft_itoa(shell->last_status));
	}
	if (str[start] == '$')
	{
		*i = start + 1;
		return (ft_itoa(getpid()));
	}
	if (str[start] == '\0' || str[start] == ' ' || str[start] == '\t'
		|| str[start] == '"' || str[start] == '\'')
	{
		*i = start;
		return (ft_strdup("$"));
	}
	return (NULL);
}

char	*build_numeric_var_value(char *str, int *i, char *value)
{
	char	c[2];
	char	*tmp;

	c[1] = '\0';
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		c[0] = str[*i];
		tmp = value;
		value = ft_strjoin(tmp, c);
		free(tmp);
		(*i)++;
	}
	return (value);
}

char	*process_regular_var(char *str, int *i, int start, t_shell *shell)
{
	int		end;
	char	*key;
	char	*value;

	end = start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	key = ft_substr(str, start, end - start);
	if (!key)
		return (ft_strdup(""));
	value = get_env_value(key, shell);
	*i = end;
	free(key);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static void	handle_token_expansion(t_token *current, char *expanded)
{
	t_token	*split_tokens;
	t_token	*last_split;

	if (should_split_token(current->value, expanded))
	{
		split_tokens = split_expanded_token(expanded, current->type);
		if (split_tokens)
		{
			last_split = split_tokens;
			while (last_split->next)
				last_split = last_split->next;
			last_split->next = current->next;
			free(current->value);
			current->value = ft_strdup(split_tokens->value);
			current->next = split_tokens->next;
			free(split_tokens->value);
			free(split_tokens);
		}
		else
		{
			free(current->value);
			current->value = expanded;
		}
		free(expanded);
	}
	else
	{
		free(current->value);
		current->value = expanded;
	}
}

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*current;
	t_token	*next;
	char	*expanded;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD)
		{
			expanded = expand_token_segments(current->value, shell);
			if (expanded)
				handle_token_expansion(current, expanded);
		}
		current = next;
	}
}
