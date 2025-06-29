/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/29 04:55:45 by ndehmej          ###   ########.fr       */
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
	if (str[start] == '\0' || str[start] == ' ' || str[start] == '\t'
		|| str[start] == '"' || str[start] == '\'')
	{
		*i = start;
		return (ft_strdup("$"));
	}
	return (NULL);
}

static char	*expand_regular_var(char *str, int *i, t_shell *shell)
{
	int		start;
	int		end;
	char	*key;
	char	*value;
	char	c[2] = {str[*i], '\0'};
	char	*tmp;

	start = *i + 1;
	end = start;
	if (!str[start] || (!ft_isalpha(str[start]) && str[start] != '_'
			&& !ft_isdigit(str[start])))
	{
		*i = start;
		return (ft_strdup("$"));
	}
	if (ft_isdigit(str[start]))
	{
		*i = start + 1;
		key = ft_substr(str, start, 1);
		value = ft_strjoin("$", key);
		free(key);
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		{
			tmp = value;
			value = ft_strjoin(tmp, c);
			free(tmp);
			(*i)++;
		}
		return (value);
	}
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

static char	*expand_in_double_quotes(char *str, int start, int end,
		t_shell *shell)
{
	char	*result;
	char	*temp;
	char	*var_value;
	int		i;
	int		seg_start;

	result = ft_strdup("");
	i = start;
	while (i < end)
	{
		seg_start = i;
		while (i < end && str[i] != '$')
			i++;
		if (i > seg_start)
		{
			temp = ft_substr(str, seg_start, i - seg_start);
			result = join_and_free(result, temp);
		}
		if (i < end && str[i] == '$')
		{
			var_value = expand_variable(str, &i, shell);
			result = join_and_free(result, var_value);
		}
	}
	return (result);
}

static char	*expand_outside_quotes(char *str, int start, int end,
		t_shell *shell)
{
	char	*result;
	char	*temp;
	char	*var_value;
	int		i;
	int		seg_start;

	result = ft_strdup("");
	i = start;
	while (i < end)
	{
		seg_start = i;
		while (i < end && str[i] != '$')
			i++;
		if (i > seg_start)
		{
			temp = ft_substr(str, seg_start, i - seg_start);
			result = join_and_free(result, temp);
		}
		if (i < end && str[i] == '$')
		{
			var_value = expand_variable(str, &i, shell);
			result = join_and_free(result, var_value);
		}
	}
	return (result);
}

static char	*expand_token_segments(char *str, t_shell *shell)
{
	char	*result;
	char	*segment_result;
	int		i;
	int		start;
	char	quote;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			start = i + 1;
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
			{
				if (quote == '\'')
				{
					segment_result = ft_substr(str, start, i - start);
				}
				else
				{
					segment_result = expand_in_double_quotes(str, start, i,
							shell);
				}
				result = join_and_free(result, segment_result);
				i++;
			}
			else
			{
				segment_result = ft_substr(str, start - 1, i - start + 1);
				result = join_and_free(result, segment_result);
			}
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			segment_result = expand_outside_quotes(str, start, i, shell);
			result = join_and_free(result, segment_result);
		}
	}
	return (result);
}

static int	should_split_token(char *original, char *expanded)
{
	int	i;

	i = 0;
	while (original[i])
	{
		if (original[i] == '\'' || original[i] == '"')
			return (0);
		i++;
	}
	i = 0;
	while (expanded[i])
	{
		if (expanded[i] == ' ' || expanded[i] == '\t' || expanded[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static t_token	*split_expanded_token(char *expanded, t_token_type type)
{
	char	**split_values;
	t_token	*new_tokens;
	t_token	*current;
	t_token	*tmp;
	int		i;
	char	*clean;

	clean = expanded;
	i = 0;
	while (clean[i])
	{
		if (clean[i] == '\t' || clean[i] == '\n')
			clean[i] = ' ';
		i++;
	}
	split_values = ft_split(clean, ' ');
	if (!split_values || !split_values[0])
	{
		if (split_values)
			ft_free_split(split_values);
		return (NULL);
	}
	new_tokens = NULL;
	i = 0;
	while (split_values[i])
	{
		if (ft_strlen(split_values[i]) == 0)
		{
			i++;
			continue ;
		}
		tmp = malloc(sizeof(t_token));
		if (!tmp)
			break ;
		tmp->type = type;
		tmp->value = ft_strdup(split_values[i]);
		tmp->next = NULL;
		if (!new_tokens)
			new_tokens = tmp;
		else
		{
			current = new_tokens;
			while (current->next)
				current = current->next;
			current->next = tmp;
		}
		i++;
	}
	ft_free_split(split_values);
	return (new_tokens);
}

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token *current;
	t_token *next;
	char *expanded;
	t_token *split_tokens;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD)
		{
			expanded = expand_token_segments(current->value, shell);
			if (expanded)
			{
				if (should_split_token(current->value, expanded))
				{
					split_tokens = split_expanded_token(expanded,
							current->type);
					if (split_tokens)
					{
						t_token *last_split = split_tokens;
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
		}
		current = next;
	}
}