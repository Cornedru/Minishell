/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 06:45:44 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quoted_segment(char *str, int *i, t_sys *sys, char **result)
{
	char	quote;

	quote = str[*i];
	if (quote == '\'')
		handle_single_quote(str, i, result);
	else
		handle_double_quote(str, i, sys, result);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	result = gc_strjoin(s1, s2);
	gc_free(s1);
	gc_free(s2);
	return (result);
}

char	*expand_token_value(char *str, t_sys *sys)
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
			handle_quote_section(str, &i, &result, sys);
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

char	*expand_outside_quotes(char *str, int start, int end, t_sys *sys)
{
	char	*result;
	int		i;
	int		seg_start;

	result = gc_strdup("");
	i = start;
	while (i < end)
	{
		seg_start = i;
		while (i < end && str[i] != '$')
			i++;
		result = gc_strjoin_free_s1(result, process_segment(str, &i, seg_start,
					sys));
	}
	return (result);
}
