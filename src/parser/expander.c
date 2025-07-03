/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 06:50:00 by ndehmej          ###   ########.fr       */
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

char	*process_segment(char *str, int *i, int seg_start, t_sys *sys)
{
	char	*temp;
	char	*var_value;
	char	*result;

	result = gc_strdup("");
	if (*i > seg_start)
	{
		temp = gc_substr(str, seg_start, *i - seg_start);
		result = gc_strjoin_free_s1(result, temp);
	}
	if (*i < (int)ft_strlen(str) && str[*i] == '$')
	{
		var_value = expand_variable(str, i, sys);
		result = gc_strjoin_free_s1(result, var_value);
	}
	return (result);
}

static char	*expand_quoted_content(char *str, int start, int end, t_sys *sys)
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

static char	*expand_in_quotes(char *str, t_expand_params *params, t_sys *sys)
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
