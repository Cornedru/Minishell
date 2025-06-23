static int	count_commands(t_ast *node)
{
	if (node->type != AST_PIPELINE)
		return (1);
	return (count_commands(node->left) + count_commands(node->right));
}

static void	execute_pipeline_child(t_ast *node, int **pipes, int cmd_index,
		int total_cmds, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;

	setup_child_signals();
	if (cmd_index > 0) /* Not first command */
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	if (cmd_index < total_cmds - 1) /* Not last command */
	{
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
	for (int i = 0; i < total_cmds - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	if (setup_redirections(node->redirs) == -1)
		exit(1);
	if (is_builtin(node->argv[0]))
	{
		exit(execute_builtin(node, shell));
	}
	else
	{
		cmd_path = find_command_path(node->argv[0], shell);
		envp = env_to_array(shell->env);
		if (!cmd_path)
			exit(127);
		execve(cmd_path, node->argv, envp);
		exit(127);
	}
}

int	execute_pipeline(t_ast *node, t_shell *shell)
{
	int cmd_count = count_commands(node);
	int **pipes = malloc(sizeof(int *) * (cmd_count - 1));
	pid_t *pids = malloc(sizeof(pid_t) * cmd_count);
	int status, last_status = 0;

	for (int i = 0; i < cmd_count - 1; i++)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
	}

	t_ast *current = node;
	for (int i = 0; i < cmd_count; i++)
	{
		if (current->type == AST_PIPELINE)
		{
			pids[i] = fork();
			if (pids[i] == 0)
				execute_pipeline_child(current->left, pipes, i, cmd_count,
					shell);
			current = current->right;
		}
		else
		{
			pids[i] = fork();
			if (pids[i] == 0)
				execute_pipeline_child(current, pipes, i, cmd_count, shell);
		}
	}

	for (int i = 0; i < cmd_count - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}

	for (int i = 0; i < cmd_count; i++)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
			last_status = WEXITSTATUS(status);
	}

	free(pipes);
	free(pids);
	return (last_status);
}