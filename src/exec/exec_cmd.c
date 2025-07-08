/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:53:11 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/05 23:20:14 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * execute_builtin - Execute built-in command
 *
 * @param node ast node containing command name
 * @param sys system structure
 *
 * @return Return value of called built-in function (exit code). 1 if call
 * failed.
 */
int	execute_builtin(t_ast *node, t_sys *sys)
{
	if (!ft_strcmp(node->args[0], "cd"))
		return (builtin_cd(node, sys));
	if (!ft_strcmp(node->args[0], "echo"))
		return (builtin_echo(node));
	if (!ft_strcmp(node->args[0], "env"))
		return (builtin_env(sys));
	if (!ft_strcmp(node->args[0], "exit"))
		return (builtin_exit(node, sys));
	if (!ft_strcmp(node->args[0], "export"))
		return (builtin_export(node, sys));
	if (!ft_strcmp(node->args[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(node->args[0], "unset"))
		return (builtin_unset(node, sys));
	(void)node;
	(void)sys;
	return (1);
}

/**
 * is_builtin - Check if command if built-in
 *
 * @return 0 = not built-in. 1 = fork built-in. 2 = non fork built-in.
 */
int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env"))
		return (1);		// These can be forked
	if (!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "cd")
		||!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "exit"))
		return (2);		// These MUST NOT be forked
	return (0);
}

/**
 * execute_external - Execute external (non built-in) command
 *
 * @param node AST linked list
 * @param sys system struct
 * 
 * @return 1 = error. 0 = no error.
 */
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

/**
 * execute_forked_cmd - Execute command in child process
 *
 * @param node AST linked list
 * @param sys system struct
 * 
 * @return Exit code from child process.
 */
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

/**
 * execute_cmd - Execute command
 *
 * @param node AST linked list
 * @param sys system struct
 * 
 * @return Exit code from command.
 */
int	execute_cmd(t_ast *node, t_sys *sys)
{
	if (is_builtin(node->args[0]) == 2)
		return (execute_builtin(node, sys));
	return (execute_forked_cmd(node, sys));
}
