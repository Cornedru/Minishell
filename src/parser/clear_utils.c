/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 18:11:37 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear(void)
{
	write(1, "\033[H\033[2J", 7);
}

static char	*expand_segment(char *str, int start, int end, t_shell *shell)
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

char	*expand_in_double_quotes(char *str, int start, int end, t_shell *shell)
{
	return (expand_segment(str, start, end, shell));
}

static char	*handle_digit_var(char *str, int *i, char *key, char *value)
{
	char	c[2];
	char	*tmp;
	(void) *key;

	c[1] = '\0';
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		c[0] = str[*i];
		tmp = value;
		value = ft_strjoin(tmp, c);
		free(tmp);
		(*i)++;
	}
	return (value);
}

char	*expand_regular_var(char *str, int *i, t_shell *shell)
{
	int		start;
	int		end;
	char	*key;
	char	*value;

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
		return (handle_digit_var(str, i, key, value));
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

int	should_split_token(char *original, char *expanded)
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