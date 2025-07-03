/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:53:11 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 06:27:55 by ndehmej          ###   ########.fr       */
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
            exit(execute_external(node, sys));
    }
    // ---- I AM THE PARENT PROCESS ----
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

int	execute_cmd(t_ast *node, t_sys *sys)
{
    if (!node->args || !node->args[0])
        return (0);
    if (is_builtin(node->args[0]) == 1)
        return (execute_builtin(node, sys));
    else
        return (execute_forked_cmd(node, sys));
}

// REMOVE THIS FUNCTION - it's already defined in exec.c
/* 
int	execute(t_ast *node, t_sys *sys)
{
    // Remove this duplicate function
}
*/
