/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/02 21:45:58 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_numeric_var(char *str, int *i, int start)
{
	char	*key;
	char	*value;

	*i = start + 1;
	key = ft_substr(str, start, 1);
	value = ft_strjoin("$", key);
	free(key);
	return (build_numeric_var_value(str, i, value));
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
