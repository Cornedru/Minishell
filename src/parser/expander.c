/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 02:54:55 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_variable(char *str, int *i, t_sys *sys)
{
	char	*result;
	int		start;
	int		end;
	char	*key;
	char	*value;

	result = expand_special_var(str, i, sys);
	if (result)
		return (result);
	start = *i + 1;
	if (!str[start] || (!ft_isalpha(str[start]) && str[start] != '_'
			&& !ft_isdigit(str[start])))
	{
		*i = start;
		return (gc_strdup("$"));
	}
	if (ft_isdigit(str[start]))
	{
		*i = start + 1;
		return (gc_strdup(""));
	}
	end = start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	key = gc_substr(str, start, end - start);
	if (!key)
		return (gc_strdup(""));
	value = get_env_var(key, sys->env_lst);
	*i = end;
	gc_free(key);
	if (value)
		return (gc_strdup(value));
	return (gc_strdup(""));
}

char	*expand_in_quotes(char *str, int start, int end, t_sys *sys, char quote)
{
	char	*result;
	char	*temp;
	char	*var_value;
	int		i;
	int		seg_start;

	if (quote == '\'')
	{
		return (gc_substr(str, start, end - start));
	}
	result = gc_strdup("");
	i = start;
	while (i < end)
	{
		seg_start = i;
		while (i < end && str[i] != '$')
			i++;
		if (i > seg_start)
		{
			temp = gc_substr(str, seg_start, i - seg_start);
			result = gc_strjoin_free_s1(result, temp);
		}
		if (i < end && str[i] == '$')
		{
			var_value = expand_variable(str, &i, sys);
			result = gc_strjoin_free_s1(result, var_value);
		}
	}
	return (result);
}

char	*expand_outside_quotes(char *str, int start, int end, t_sys *sys)
{
	char	*result;
	char	*temp;
	char	*var_value;
	int		i;
	int		seg_start;

	result = gc_strdup("");
	i = start;
	while (i < end)
	{
		seg_start = i;
		while (i < end && str[i] != '$')
			i++;
		if (i > seg_start)
		{
			temp = gc_substr(str, seg_start, i - seg_start);
			result = gc_strjoin_free_s1(result, temp);
		}
		if (i < end && str[i] == '$')
		{
			var_value = expand_variable(str, &i, sys);
			result = gc_strjoin_free_s1(result, var_value);
		}
	}
	return (result);
}

char	*expand_token_value(char *str, t_sys *sys)
{
	char	*result;
	char	*segment_result;
	int		i;
	int		start;
	char	quote;

	result = gc_strdup("");
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
			segment_result = expand_in_quotes(str, start, i, sys, quote);
			result = gc_strjoin_free_s1(result, segment_result);
			if (str[i] == quote)
				i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			segment_result = expand_outside_quotes(str, start, i, sys);
			result = gc_strjoin_free_s1(result, segment_result);
		}
	}
	return (result);
}

void	expand_tokens(t_token *tokens, t_sys *sys)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded = expand_token_value(current->value, sys);
			if (expanded)
			{
				gc_free(current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
}
