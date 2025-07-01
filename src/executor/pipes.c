/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 18:30:05 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands_in_pipeline(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type != AST_PIPELINE)
		return (1);
	return (count_commands_in_pipeline(node->left) + 
			count_commands_in_pipeline(node->right));
}

static int	**create_pipes(int total_cmds)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (total_cmds - 1));
	if (!pipes)
		return (NULL);
		
	for (i = 0; i < total_cmds - 1; i++)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			return (NULL);
		}
	}
	return (pipes);
}

static void	cleanup_pipes(int **pipes, int total_cmds)
{
	int	i;

	for (i = 0; i < total_cmds - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
}

static void	setup_pipe_fds(int **pipes, int cmd_index, int total_cmds)
{
	int	i;

	// Setup input from previous command
	if (cmd_index > 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
			exit(1);
	}
	
	// Setup output to next command
	if (cmd_index < total_cmds - 1)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
			exit(1);
	}
	
	// Close all pipes
	for (i = 0; i < total_cmds - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

int	setup_redirections(t_redir *redirs)
{
	t_redir	*current;
	int		fd;

	current = redirs;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
		{
			fd = open(current->file, O_RDONLY);
			if (fd == -1)
			{
				perror(current->file);
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (current->type == TOKEN_REDIR_OUT)
		{
			fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(current->file);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (current->type == TOKEN_REDIR_APPEND)
		{
			fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(current->file);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (current->type == TOKEN_HEREDOC)
		{
			if (handle_heredoc(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

static void	execute_child_in_pipeline(t_ast *node, int **pipes, int cmd_index, 
									int total_cmds, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;

	setup_child_signals();
	setup_pipe_fds(pipes, cmd_index, total_cmds);
	
	if (setup_redirections(node->redirs) == -1)
		exit(1);
		
	if (node->argv && node->argv[0])
	{
		if (is_builtin(node->argv[0]))
			exit(execute_builtin(node, shell));
			
		cmd_path = find_command_path(node->argv[0], shell);
		if (!cmd_path)
		{
			ft_putstr_fd(node->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		
		envp = env_to_array(shell->env);
		execve(cmd_path, node->argv, envp);
		perror("execve");
		exit(126);
	}
	exit(0);
}

static void	execute_pipeline_recursive(t_ast *node, int **pipes, 
										int cmd_index, int total_cmds, 
										t_shell *shell)
{
	pid_t	pid;

	if (!node)
		return;

	if (node->type == AST_COMMAND)
	{
		pid = fork();
		if (pid == 0)
			execute_child_in_pipeline(node, pipes, cmd_index, total_cmds, shell);
		else if (pid < 0)
			perror("fork");
	}
	else if (node->type == AST_PIPELINE)
	{
		execute_pipeline_recursive(node->left, pipes, cmd_index, total_cmds, shell);
		execute_pipeline_recursive(node->right, pipes, 
									cmd_index + count_commands_in_pipeline(node->left), 
									total_cmds, shell);
	}
}

static int	wait_for_children(int total_cmds)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < total_cmds)
	{
		wait(&status);
		if (i == total_cmds - 1)  // Last command determines exit status
		{
			if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGINT)
					last_status = 130;
				else if (sig == SIGQUIT)
					last_status = 131;
				else
					last_status = 128 + sig;
			}
			else
				last_status = WEXITSTATUS(status);
		}
		i++;
	}
	return (last_status);
}

int	execute_pipeline(t_ast *ast, t_shell *shell)
{
	int		total_cmds;
	int		**pipes;
	int		last_status;

	total_cmds = count_commands_in_pipeline(ast);
	if (total_cmds == 1)
		return (execute_command(ast, shell));
	
	pipes = create_pipes(total_cmds);
	if (!pipes)
		return (1);
	
	execute_pipeline_recursive(ast, pipes, 0, total_cmds, shell);
	cleanup_pipes(pipes, total_cmds);
	last_status = wait_for_children(total_cmds);
	
	return (last_status);
}

// Helper function for setup_redirections
