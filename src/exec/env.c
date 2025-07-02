/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 00:38:16 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/02 23:17:56 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * env_getarray - make char **envp back from t_env *envp
 *
 * @envp: environment linked list
 * 
 * Return: envp array of strings.
 */
char	**env_getarray(t_env *envp)
{
	int		i;
	int		count;
	char	**array;

	count = ft_envsize(envp);
	array = (char **)gc_malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (++i < count)
	{
		if (!envp->content)
			array[i] = gc_strdup(envp->var);
		else
			array[i] = gc_strjoin_free_s1(gc_strjoin(envp->var, "="),
					envp->content);
		envp = envp->next;
	}
	array[i] = NULL;
	return (array);
}

int	set_env_var(t_env **envp, char *var_name, char *content)
{
	t_env	*current;
	t_env	*new_node;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->var, var_name))
		{
			gc_free(current->content);
			current->content = gc_strdup(content);
			if (!current->content)
				return (1);
			return (0);
		}
		current = current->next;
	}
	new_node = gc_envnew(var_name, gc_strdup(content));
	if (!new_node)
		return (1);
	ft_envadd_back(envp, new_node);
	return (0);
}

char	*get_env_var(char *var_name, t_env *envp)
{
	int	len;
	int	i;

	len = ft_strlen(var_name);
	i = 0;
	while (envp)
	{
		if (!ft_strcmp(envp->var, var_name))
			return (envp->content);
		envp = envp->next;
	}
	return (NULL);
}

/* char	*get_env_var(char *var_name, char **envp)
{
	int	len;
	int	i;

	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);		// Return pointer to the start of the value
		i++;
	}
	return (NULL);
} */

/* static char	*get_envp_var_name(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (gc_substr(env, 0, i));
} */

t_env	*pull_env(char **envp)
{
	t_env	*env_lst;
	char	*var;
	char	*content;
	char	*equal_sign;
	int		i;

	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			var = gc_substr(envp[i], 0, equal_sign - envp[i]);
			content = gc_strdup(equal_sign + 1);
		}
		else
		{
			var = gc_strdup(envp[i]);
			content = NULL;
		}
		ft_envadd_back(&env_lst, gc_envnew(var, content));
		i++;
	}
	return (env_lst);
}

/* t_env	*pull_env(char **envp)
{
	t_env	*env_lst;
	char	*var;
	char	*content;
	int		len;
	int		i;

	i = 0;
	while (envp[i])
	{
		var = get_envp_var_name(envp[i]);
		len = ft_strlen(envp[i]) - ft_strlen(var);
		content = gc_substr(envp[i], ft_strlen(var), len);
		ft_envadd_back(&env_lst, gc_envnew(var, content));
		i++;
	}
	return (env_lst);
} */
