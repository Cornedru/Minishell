/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 06:43:24 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_numeric_var(char *str, int *i, int start)
{
	(void)str;
	*i = start + 1;
	return (gc_strdup(""));
}

char	*expand_token_segments(char *str, t_sys *sys)
{
	char	*result;
	char	*segment_result;
	int		i;
	int		start;

	result = gc_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			handle_quoted_segment(str, &i, sys, &result);
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			segment_result = expand_outside_quotes(str, start, i, sys);
			result = join_and_free(result, segment_result);
		}
	}
	return (result);
}

char	*normalize_whitespace(char *expanded)
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

char	*process_regular_var(char *str, int *i, int start, t_sys *sys)
{
	int		end;
	char	*key;
	char	*value;

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
