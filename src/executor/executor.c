#include "minishell.h"

static int	is_builtin(char *cmd)
{
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", NULL};
	int		i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static char	*find_command_path(char *cmd, t_shell *shell)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/')) /* Absolute or relative path */
		return (access(cmd, X_OK) == 0 ? ft_strdup(cmd) : NULL);
	path_env = get_env_value("PATH", shell);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

static int	setup_redirections(t_redir *redirs)
{
	int	fd;

	while (redirs)
	{
		if (redirs->type == REDIR_IN)
		{
			fd = open(redirs->file, O_RDONLY);
			if (fd == -1)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == REDIR_OUT)
		{
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (-1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->type == REDIR_APPEND)
		{
			fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (-1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->type == REDIR_HEREDOC)
		{
			/* Handle heredoc (implemented separately) */
			if (handle_heredoc(redirs) == -1)
				return (-1);
		}
		redirs = redirs->next;
	}
	return (0);
}

static int	execute_command(t_ast *node, t_shell *shell)
{
	char *cmd_path;
	char **envp;
	pid_t pid;
	int status;

	if (!node->argv || !node->argv[0])
		return (0);

	/* Check if builtin */
	if (is_builtin(node->argv[0]))
		return (execute_builtin(node, shell));

	/* Find command path */
	cmd_path = find_command_path(node->argv[0], shell);
	if (!cmd_path)
	{
		printf("minishell: %s: command not found\n", node->argv[0]);
		return (127);
	}

	pid = fork();
	if (pid == 0) /* Child process */
	{
		setup_child_signals();

		if (setup_redirections(node->redirs) == -1)
			exit(1);

		envp = env_to_array(shell->env);
		execve(cmd_path, node->argv, envp);
		perror("execve");
		exit(127);
	}
	else if (pid > 0) /* Parent process */
	{
		free(cmd_path);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}

	free(cmd_path);
	return (-1);
}