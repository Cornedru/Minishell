/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:53:11 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 01:00:48 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_external(t_ast *node, t_sys *sys)
{
	char	*cmd_path;

	cmd_path = find_cmd_path(sys, node->args[0]);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);			// Standard exit code for command not found
	}
	execve(cmd_path, node->args, sys->envp);
	ft_putstr_fd("minishell: ", 2);	// If we get here, execve failed.
	perror(node->args[0]);	// Perror will print the system error
	gc_free(cmd_path);		// Free the path if execve fails
	exit(126);				// Standard exit code for command not executable
}

int	execute_forked_cmd(t_ast *node, t_sys *sys)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)	// ---- I AM A FAILURE ----
		return (1);
	if (pid == 0)	// ---- I AM THE CHILD PROCESS ----
	{
		if (is_builtin(node->args[0]) == 1)
			exit(execute_builtin(node, sys));
		else
			execute_external(node, sys);
	}

	// PARENTING
    waitpid(pid, &status, 0);	// Wait for child
    return (WEXITSTATUS(status));	// return the exit code from the child
}

int	execute_cmd(t_ast *node, t_sys *sys)
{
	if (is_builtin(node->args[0]) == 2)
		return (execute_builtin(node, sys));
	return (execute_forked_cmd(node, sys));
}
