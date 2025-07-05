/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:59:21 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/06 00:15:57 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_shlvl(t_sys *sys)
{
	char	*tmp;
	int		shlvl;

	tmp = gc_strdup(get_env_var("SHLVL", sys->env_lst));
	shlvl = ft_atoi(tmp) + 1;
	if (tmp)
		shlvl++;
	set_env_var(sys, &sys->env_lst, "SHLVL", ft_itoa(shlvl));
	gc_free(tmp);
}

/**
 * pull_env -  copy envp array into linked list
 *
 * @param envp environment array of strings
 * 
 * @return env_lst environment linked list.
 */
t_env	*pull_env(char **envp)
{
	t_env	*env_lst;
	char	*var;
	char	*content;
	char	*equal_sign;
	int		i;

	env_lst = NULL;
	i = -1;
	while (envp[++i])
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
	}
	return (env_lst);
}

/**
 * init_sys - initialize system struct
 *
 * @param sys system struct
 * @param envp environment array of strings
 * 
 * @return 1 = error. 0 = no error.
 */
int	init_sys(t_sys **sys, char **envp)
{
	*sys = (t_sys *)gc_malloc(sizeof(t_sys));
	if (!*sys)
		return (1);
	(*sys)->env_lst = pull_env(envp);
	(*sys)->envp = dup_array(envp);
	if (!(*sys)->env_lst || !(*sys)->envp)
		return (1);
	(*sys)->token = NULL;
	(*sys)->ast = NULL;
	(*sys)->exit = 0;
	return (0);
}

/**
 * init_shell - initialize shell program
 *
 * @param sys system struct
 * @param envp environment array of strings
 * 
 * @return 1 = error. 0 = no error.
 */
int	init_shell(t_sys **sys, char **envp)
{
	int	error;

	error = 0;
	error = init_sys(sys, envp);
	error = update_env_array(*sys);
	set_shlvl(*sys);
	return (error);
}
