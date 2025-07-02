/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:59:21 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/02 22:59:31 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
