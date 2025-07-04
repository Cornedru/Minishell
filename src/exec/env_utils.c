/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 02:30:33 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/04 02:22:52 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_identifier(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (i == 0 && !ft_isalpha(arg[i]) && arg[i] != '_')
			return (0);
		else if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
	}
	return (1);
}

int	unset_env_var(t_sys *sys, t_env **env_lst, char *var_name)
{
	t_env	*cu;
	t_env	*pv;

	if (!*env_lst)
		return (0);
	if (!ft_strcmp((*env_lst)->var, var_name))
	{
		cu = *env_lst;
		*env_lst = (*env_lst)->next;
		return (free_envnode(cu), update_env_array(sys));
	}
	pv = *env_lst;
	cu = (*env_lst)->next;
	while (cu)
	{
		if (!ft_strcmp(cu->var, var_name))
		{
			pv->next = cu->next;
			return (free_envnode(cu), update_env_array(sys));
		}
		pv = cu;
		cu = cu->next;
	}
	return (0);
}

int	set_env_var(t_sys *sys, t_env **env_lst, char *var_name, char *content)
{
	t_env	*current;
	t_env	*new_node;

	current = *env_lst;
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
	ft_envadd_back(env_lst, new_node);
	return (update_env_array(sys));
}

char	*get_env_var(char *var_name, t_env *envp)
{
	int	i;

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
