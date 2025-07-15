/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 06:44:17 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clear(void)
{
	write(1, "\033[H\033[2J", 7);
}

char	*expand_segment(char *str, int start, int end, t_sys *sys)
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
			result = join_and_free(result, temp);
		}
		if (i < end && str[i] == '$')
		{
			var_value = expand_variable(str, &i, sys);
			result = join_and_free(result, var_value);
		}
	}
	return (result);
}

char	*expand_in_double_quotes(char *str, int start, int end, t_sys *sys)
{
	return (expand_segment(str, start, end, sys));
}

void	handle_single_quote(char *str, int *i, char **result)
{
	process_quote(str, i, result, '\'');
}

void	handle_double_quote(char *str, int *i, t_sys *sys, char **result)
{
	int		start;
	char	*segment_result;

	start = *i + 1;
	(*i)++;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (str[*i] == '"')
	{
		segment_result = expand_in_double_quotes(str, start, *i, sys);
		*result = join_and_free(*result, segment_result);
		(*i)++;
	}
	else
	{
		segment_result = gc_substr(str, start - 1, *i - start + 1);
		*result = join_and_free(*result, segment_result);
	}
}
