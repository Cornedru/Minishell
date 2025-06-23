#include "minishell.h"

static void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = SIG_INTERRUPT;
		close(STDIN_FILENO);
	}
}

int	handle_heredoc(t_redir *redir)
{
	int pipe_fd[2];
	char *line;
	char *delimiter = redir->file;
	pid_t pid;
	int status;

	if (pipe(pipe_fd) == -1)
		return (-1);

	pid = fork();
	if (pid == 0) /* Child process for reading heredoc */
	{
		signal(SIGINT, heredoc_signal_handler);
		close(pipe_fd[0]); /* Close read end */

		while (1)
		{
			line = readline("> ");
			if (!line) /* EOF (Ctrl-D) */
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
	else if (pid > 0) /* Parent process */
	{
		close(pipe_fd[1]); /* Close write end */
		waitpid(pid, &status, 0);

		if (WEXITSTATUS(status) != 0 || g_signal_status == SIG_INTERRUPT)
		{
			close(pipe_fd[0]);
			return (-1);
		}

		/* Redirect stdin to read from pipe */
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}

	return (0);
}