/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/27 23:50:56 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

static t_env	*create_env_var(char *key, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	new_var->key = ft_strdup(key);
	new_var->value = value ? ft_strdup(value) : NULL;
	new_var->exported = 1;
	new_var->next = NULL;
	if (!new_var->key || (value && !new_var->value))
	{
		free(new_var->key);
		free(new_var->value);
		free(new_var);
		return (NULL);
	}
	return (new_var);
}

static void	add_env_var(t_shell *shell, char *key, char *value)
{
	t_env	*new_var;
	t_env	*current;

	new_var = create_env_var(key, value);
	if (!new_var)
		return ;
	if (!shell->env)
	{
		shell->env = new_var;
		return ;
	}
	current = shell->env;
	while (current->next)
		current = current->next;
	current->next = new_var;
}

static void	parse_env_line(char *env_line, t_shell *shell)
{
	char	*equals;
	char	*key;
	char	*value;

	equals = ft_strchr(env_line, '=');
	if (!equals)
		return ;
	*equals = '\0';
	key = env_line;
	value = equals + 1;
	add_env_var(shell, key, value);
	*equals = '=';
}

void	init_minimal_env(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	add_env_var(shell, "PWD", pwd);
	add_env_var(shell, "PATH", "/usr/bin:/bin");
	add_env_var(shell, "SHLVL", "1");
	free(pwd);
}

void	init_env_from_system(t_shell *shell)
{
	int	i;

	shell->env = NULL;
	if (!environ || !environ[0])
	{
		init_minimal_env(shell);
		return ;
	}
	i = 0;
	while (environ[i])
	{
		parse_env_line(environ[i], shell);
		i++;
	}
}

char *ft_re(char *s, int old, int new)
{
	int i = 0;
	char *res;
	if (!s)
		return (NULL);
	res = gc_malloc(sizeof(char) * new);
	if (!res) return (NULL);
	while (i >= old && s[i])
	{
		res = s[i];
		i++;
	}
	free(s);
	return (res);
}

