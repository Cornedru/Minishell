/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 06:43:58 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIG_INTERRUPT;
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
		if (g_signal == SIG_INTERRUPT)
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
	if (WEXITSTATUS(status) != 0 || g_signal == SIG_INTERRUPT)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (!delimiter)
		return (-1);
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

char	**gather_all_words(t_token **tokens)
{
	t_token	*start;
	int		count;
	char	**argv;
	int		i;

	start = *tokens;
	count = count_word_tokens(start);
	argv = (char **)gc_malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		argv[i] = gc_strdup((*tokens)->value);
		if (!argv[i])
			return (NULL);
		i++;
		advance_token(tokens);
	}
	argv[i] = NULL;
	return (argv);
}
