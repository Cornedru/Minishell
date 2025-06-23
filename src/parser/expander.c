/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:48:58 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(char *key, t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*expand_special_var(char *str, int *i, t_shell *shell)
{
	int	start;

	start = *i + 1;
	if (str[start] == '?')
	{
		*i = start + 1;
		return (ft_itoa(shell->last_status));
	}
	if (str[start] == '$')
	{
		*i = start + 1;
		return (ft_itoa(getpid()));
	}
	return (NULL);
}

static char	*expand_regular_var(char *str, int *i, t_shell *shell)
{
	int		start;
	int		end;
	char	*key;
	char	*value;

	start = *i + 1;
	end = start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	if (end == start)
	{
		*i = start;
		return (ft_strdup("$"));
	}
	key = ft_substr(str, start, end - start);
	if (!key)
		return (NULL);
	value = get_env_value(key, shell);
	*i = end;
	free(key);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*expand_variable(char *str, int *i, t_shell *shell)
{
	char	*result;

	result = expand_special_var(str, i, shell);
	if (result)
		return (result);
	return (expand_regular_var(str, i, shell));
}
