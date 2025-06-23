/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:33:58 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_ast *node, t_shell *shell)
{
	char	*cmd;

	cmd = node->argv[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (builtin_echo(node->argv));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (builtin_cd(node->argv, shell));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd, "export") == 0)
		return (builtin_export(node->argv, shell));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (builtin_unset(node->argv, shell));
	else if (ft_strcmp(cmd, "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (builtin_exit(node->argv, shell));
	return (1);
}