/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:51:35 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 01:44:05 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_ast *node, t_sys *sys)
{
	(void)node;
	(void)sys;
	// FORKED
	// NOT FORKED
	return (1);
}

/**
 * is_builtin - check if command if built-in
 *
 * Return:	0 = not built-in. 1 = fork built-in. 2 = non fork built-in.
 */
int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "exit", 5))
		return (2);
	return (0);	
}
