/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:53:11 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/02 21:53:22 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	execute(t_ast *node, t_sys *sys)
{
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (handle_pipe(node, sys));
	else if (node->type >= AST_REDIR_IN && node->type <= AST_HEREDOC)
		return (handle_redirection(node, sys));
	else if (node->type == AST_CMD)
		return (execute_cmd(node, sys));
	// else if AND/OR
	return (1);
}
