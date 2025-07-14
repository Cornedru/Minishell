/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 06:43:07 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_regular_var(char *str, int *i, t_sys *sys)
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
		return (gc_strdup("$"));
	}
	if (ft_isdigit(str[start]))
	{
		*i = start + 1;
		key = gc_substr(str, start, 1);
		value = gc_strjoin("$", key);
		gc_free(key);
		return (handle_digit_var(str, i, key, value));
	}
	key = extract_var_key(str, start, &end);
	if (!key)
		return (gc_strdup(""));
	return (get_var_value(key, sys, i, end));
}

char	*handle_digit_var(char *str, int *i, char *key, char *value)
{
	char	c[2];
	char	*tmp;

	(void)key;
	c[1] = '\0';
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		c[0] = str[*i];
		tmp = value;
		value = gc_strjoin(tmp, c);
		gc_free(tmp);
		(*i)++;
	}
	return (value);
}

char	*extract_var_key(char *str, int start, int *end)
{
	while (str[*end] && (ft_isalnum(str[*end]) || str[*end] == '_'))
		(*end)++;
	return (gc_substr(str, start, *end - start));
}

char	*get_var_value(char *key, t_sys *sys, int *i, int end)
{
	char	*value;

	value = get_env_var(key, sys->env_lst);
	*i = end;
	gc_free(key);
	if (value)
		return (gc_strdup(value));
	return (gc_strdup(""));
}

void	replace_token_value(t_token *current, t_token *split_tokens)
{
	t_token	*last_split;

	last_split = split_tokens;
	while (last_split->next)
		last_split = last_split->next;
	last_split->next = current->next;
	free(current->value);
	current->value = gc_strdup(split_tokens->value);
	current->next = split_tokens->next;
	free(split_tokens->value);
	free(split_tokens);
}
