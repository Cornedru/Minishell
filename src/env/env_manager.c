/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/29 04:50:13 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = value ? ft_strdup(value) : NULL;
	node->exported = 1;
	node->next = NULL;
	return (node);
}

char	*get_env_value(char *key, t_shell *shell)
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

void	set_env_value(char *key, char *value, t_shell *shell)
{
	t_env	*env;
	t_env	*new_node;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new_node = create_env_node(key, value);
	if (new_node)
	{
		new_node->next = shell->env;
		shell->env = new_node;
	}
}

void	init_env(t_shell *shell)
{
	int		i;
	char	*equals;
	char	*key;
	char	*value;

	shell->env = NULL;
	i = 0;
	while (environ[i])
	{
		equals = ft_strchr(environ[i], '=');
		if (equals)
		{
			*equals = '\0';
			key = environ[i];
			value = equals + 1;
			set_env_value(key, value, shell);
			*equals = '=';
		}
		i++;
	}
}