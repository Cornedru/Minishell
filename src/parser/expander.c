/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/06 06:18:54 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_invalid_or_numeric_var(char *str, int *i)
{
	int	start;

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
	return (NULL);
}

char	*extract_env_value(char *str, int *i, int start, t_sys *sys)
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

char	*expand_quoted_content(char *str, int start, int end, t_sys *sys)
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

char	*expand_in_quotes(char *str, t_expand_params *params, t_sys *sys)
{
	if (params->quote == '\'')
		return (gc_substr(str, params->start, params->end - params->start));
	return (expand_quoted_content(str, params->start, params->end, sys));
}

void	handle_quote_section(char *str, int *i, char **result, t_sys *sys)
{
	t_expand_params	params;
	char			*segment_result;

	params.quote = str[*i];
	params.start = *i + 1;
	(*i)++;
	while (str[*i] && str[*i] != params.quote)
		(*i)++;
	params.end = *i;
	segment_result = expand_in_quotes(str, &params, sys);
	*result = gc_strjoin_free_s1(*result, segment_result);
	if (str[*i] == params.quote)
		(*i)++;
}
