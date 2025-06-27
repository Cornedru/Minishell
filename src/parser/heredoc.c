/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/25 04:03:03 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = SIG_INTERRUPT;
		close(STDIN_FILENO);
	}
}

static void	heredoc_child_process(int *pipe_fd, char *delimiter)
{
	char	*line;

	signal(SIGINT, heredoc_signal_handler);
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		if (g_signal_status == SIG_INTERRUPT)
			break ;
	}
	close(pipe_fd[1]);
	exit(0);
}

static int	heredoc_parent_process(int *pipe_fd, pid_t pid)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) != 0 || g_signal_status == SIG_INTERRUPT)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}

int	handle_heredoc(t_redir *redir)
{
	int		pipe_fd[2];
	char	*delimiter;
	pid_t	pid;

	delimiter = redir->file;
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		heredoc_child_process(pipe_fd, delimiter);
	else if (pid > 0)
		return (heredoc_parent_process(pipe_fd, pid));
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (0);
}

