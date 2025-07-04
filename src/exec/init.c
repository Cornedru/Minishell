/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:59:21 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/04 01:12:56 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_sys	*init_sys(char **envp)
{
	t_sys	*sys;

	sys = (t_sys *)gc_malloc(sizeof(t_sys));
	sys->env_lst = pull_env(envp);
	sys->envp = dup_array(envp);
	sys->token = NULL;
	sys->ast = NULL;
	sys->exit = 0;
	return (sys);
}
