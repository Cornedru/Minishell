/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 18:09:28 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*normalize_whitespace(char *expanded)
{
	char	*clean;
	int		i;

	clean = expanded;
	i = 0;
	while (clean[i])
	{
		if (clean[i] == '\t' || clean[i] == '\n')
			clean[i] = ' ';
		i++;
	}
	return (clean);
}

static t_token	*create_token_list(char **split_values, t_token_type type)
{
	t_token	*new_tokens;
	t_token	*current;
	t_token	*tmp;
	int		i;

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
	return (new_tokens);
}

t_token	*split_expanded_token(char *expanded, t_token_type type)
{
	char	**split_values;
	t_token	*new_tokens;
	char	*clean;

	clean = normalize_whitespace(expanded);
	split_values = ft_split(clean, ' ');
	if (!split_values || !split_values[0])
	{
		if (split_values)
			ft_free_split(split_values);
		return (NULL);
	}
	new_tokens = create_token_list(split_values, type);
	ft_free_split(split_values);
	return (new_tokens);
}

static void	handle_quoted_segment(char *str, int *i, t_shell *shell,
								char **result)
{
	char	quote;
	int		start;
	char	*segment_result;

	quote = str[*i];
	start = *i + 1;
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
	{
		if (quote == '\'')
		{
			segment_result = ft_substr(str, start, *i - start);
		}
		else
		{
			segment_result = expand_in_double_quotes(str, start, *i, shell);
		}
		*result = join_and_free(*result, segment_result);
		(*i)++;
	}
	else
	{
		segment_result = ft_substr(str, start - 1, *i - start + 1);
		*result = join_and_free(*result, segment_result);
	}
}

char	*expand_token_segments(char *str, t_shell *shell)
{
	char	*result;
	char	*segment_result;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			handle_quoted_segment(str, &i, shell, &result);
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

char	*expand_outside_quotes(char *str, int start, int end, t_shell *shell)
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

char	*expand_variable(char *str, int *i, t_shell *shell)
{
	char	*result;
	int		start;

	result = expand_special_var(str, i, shell);
	if (result)
		return (result);
	start = *i + 1;
	if (!str[start] || (!ft_isalpha(str[start]) && str[start] != '_'
			&& !ft_isdigit(str[start])))
	{
		*i = start;
		return (ft_strdup("$"));
	}
	if (ft_isdigit(str[start]))
		return (handle_numeric_var(str, i, start));
	return (process_regular_var(str, i, start, shell));
}

char	*join_and_free(char *s1, char *s2)
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