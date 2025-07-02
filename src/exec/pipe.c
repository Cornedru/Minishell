/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:50:11 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/02 21:50:24 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	left_child(t_ast *node, t_sys *sys, int *pipe_fd)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	exit(execute(node->left, sys));
}

void	right_child(t_ast *node, t_sys *sys, int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	exit(execute(node->right, sys));
}

int	handle_pipe(t_ast *node, t_sys *sys)
{
	pid_t	pid_l;
	pid_t	pid_r;
	int		status;
	int		pipe_fd[2];

	if(pipe(pipe_fd) == -1)
		return (1);

	// LEFT
	pid_l = fork();
	if (pid_l == -1)	// ---- I AM A FAILURE ----
		return (1);
	else if (pid_l == 0)
		left_child(node, sys, pipe_fd);

	// RIGHT
	pid_r = fork();
	if (pid_r == -1)	// ---- I AM A FAILURE ----
		return (1);
	else if (pid_r == 0)
		right_child(node, sys, pipe_fd);

	// PARENTING
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_l, NULL, 0);	// Wait for left (don't need its status)
	waitpid(pid_r, &status, 0);	// Wait for right
	return (WEXITSTATUS(status));
}
