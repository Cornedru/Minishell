/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 04:51:30 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_special_var(char *str, int *i, t_shell *shell)
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
	return (NULL);
}

static char	*expand_regular_var(char *str, int *i, t_shell *shell)
{
	int		start;
	int		end;
	char	*key;
	char	*value;

	start = *i + 1;
	end = start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	if (end == start)
	{
		*i = start;
		return (ft_strdup("$"));
	}
	key = ft_substr(str, start, end - start);
	if (!key)
		return (NULL);
	value = get_env_value(key, shell);
	*i = end;
	free(key);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*expand_variable(char *str, int *i, t_shell *shell)
{
	char	*result;

	result = expand_special_var(str, i, shell);
	if (result)
		return (result);
	return (expand_regular_var(str, i, shell));
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*expand_string_outside_quotes(char *str, t_shell *shell)
{
	char	*result;
	char	*temp;
	char	*var_value;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '$')
			i++;
		if (i > start)
		{
			temp = ft_substr(str, start, i - start);
			result = join_and_free(result, temp);
		}
		if (str[i] == '$')
		{
			var_value = expand_variable(str, &i, shell);
			result = join_and_free(result, var_value);
		}
	}
	return (result);
}

static char	*expand_string_in_double_quotes(char *str, t_shell *shell)
{
	char	*result;
	char	*temp;
	char	*var_value;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 1; // Skip opening quote
	while (str[i] && str[i] != '"')
	{
		start = i;
		while (str[i] && str[i] != '$' && str[i] != '"')
			i++;
		if (i > start)
		{
			temp = ft_substr(str, start, i - start);
			result = join_and_free(result, temp);
		}
		if (str[i] == '$')
		{
			var_value = expand_variable(str, &i, shell);
			result = join_and_free(result, var_value);
		}
	}
	return (result);
}

static char	*expand_string_in_single_quotes(char *str)
{
	int		len;
	char	*result;

	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		result = ft_substr(str, 1, len - 2);
	else
		result = ft_strdup(str);
	return (result);
}

// static int	is_quoted_string(char *str)
// {
// 	int	len;

// 	len = ft_strlen(str);
// 	if (len >= 2)
// 	{
// 		if ((str[0] == '\'' && str[len - 1] == '\'') ||
// 			(str[0] == '"' && str[len - 1] == '"'))
// 			return (1);
// 	}
// 	return (0);
// }

static char	*expand_token_value(char *str, t_shell *shell)
{
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (expand_string_in_single_quotes(str));
	else if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (expand_string_in_double_quotes(str, shell));
	else
		return (expand_string_outside_quotes(str, shell));
}

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded = expand_token_value(current->value, shell);
			if (expanded)
			{
				free(current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
}