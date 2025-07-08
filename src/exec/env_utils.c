/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 02:30:33 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/06 00:13:26 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_valid_identifier - Check if argument is a valid environment variable.
 * 
 * @param arg string to check
 * 
 * @return 1 = yes. 0 = no.
 */
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

/**
 * unset_env_var - Remove environment variable to value.
 * 
 * @param sys system struct
 * @param env_lst environment linked list
 * @param var_name variable name
 * 
 * @return 1 = error. 0 = no error.
 */
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

/**
 * set_env_var - Set environment variable to value. Create variable if needed.
 *
 * @param node: ast linked list
 * @param sys: system struct
 * 
 * @return 1 = error. 0 = no error.
 */
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

/**
 * get_env_var - Get environment variable value
 *
 * @param var_name: variable name
 * @param env_lst: environment linked list
 *
 * @return Pointer to value of var_name.
 */
char	*get_env_var(char *var_name, t_env *env_lst)
{
	int	i;

	i = 0;
	while (env_lst)
	{
		if (!ft_strcmp(env_lst->var, var_name))
			return (env_lst->content);
		env_lst = env_lst->next;
	}
	return (NULL);
}
