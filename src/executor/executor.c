/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/28 23:47:13 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	char	*builtins[8];
	int		i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static char	*find_command_in_paths(char **paths, char *cmd)
{
	char	*temp;
	char	*full_path;
	int		i;

	i = 0;
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
	return (NULL);
}

char	*find_command_path(char *cmd, t_shell *shell)
{
	char		*path_env;
	char		**paths;
	char		*result;
	struct stat	st;

	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": Is a directory\n", 2);
				shell->last_status = 126;
				return (NULL);
			}
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			shell->last_status = 126;
			return (NULL);
		}
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->last_status = 127;
		return (NULL);
	}
	path_env = get_env_value("PATH", shell);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths || !*paths)
		return (NULL);
	result = find_command_in_paths(paths, cmd);
	ft_free_split(paths);
	return (result);
}

static int	setup_redirections(t_redir *redirs)
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
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(current->file, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				return (-1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (current->type == TOKEN_REDIR_OUT)
		{
			fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(current->file, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				return (-1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (current->type == TOKEN_REDIR_APPEND)
		{
			fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(current->file, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				return (-1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				close(fd);
				return (-1);
			}
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

static int	execute_builtin_with_redirections(t_ast *ast, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;
	int	status;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	
	if (setup_redirections(ast->redirs) == -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
		return (1);
	}
	
	status = execute_builtin(ast, shell);
	
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	
	return (status);
}

int	execute_command(t_ast *ast, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;
	pid_t	pid;
	int		status;

	if (!ast || !ast->argv || !ast->argv[0])
		return (1);
		
	// Handle empty command (just redirections)
	if (ast->argv[0][0] == '\0')
	{
		if (setup_redirections(ast->redirs) == -1)
			return (1);
		return (0);
	}
	
	if (is_builtin(ast->argv[0]))
		return (execute_builtin_with_redirections(ast, shell));
	
	cmd_path = find_command_path(ast->argv[0], shell);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ast->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	
	envp = env_to_array(shell->env);
	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		if (setup_redirections(ast->redirs) == -1)
			exit(1);
		execve(cmd_path, ast->argv, envp);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
		ft_free_split(envp);
		if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGINT)
				return (130);
			else if (sig == SIGQUIT)
			{
				ft_putstr_fd("Quit (core dumped)\n", 2);
				return (131);
			}
			return (128 + sig);
		}
		return (WEXITSTATUS(status));
	}
	else
	{
		perror("fork");
		free(cmd_path);
		ft_free_split(envp);
		return (1);
	}
}

static int	count_commands_in_pipeline(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type != AST_PIPELINE)
		return (1);
	return (count_commands_in_pipeline(node->left) + 
			count_commands_in_pipeline(node->right));
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
		{
			setup_child_signals();
			
			// Setup pipes
			if (cmd_index > 0)
			{
				if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
					exit(1);
			}
			if (cmd_index < total_cmds - 1)
			{
				if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
					exit(1);
			}
			
			// Close all pipes
			for (int i = 0; i < total_cmds - 1; i++)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
			
			if (setup_redirections(node->redirs) == -1)
				exit(1);
				
			if (node->argv && node->argv[0])
			{
				if (is_builtin(node->argv[0]))
					exit(execute_builtin(node, shell));
					
				char *cmd_path = find_command_path(node->argv[0], shell);
				if (!cmd_path)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(node->argv[0], 2);
					ft_putstr_fd(": command not found\n", 2);
					exit(127);
				}
				
				char **envp = env_to_array(shell->env);
				execve(cmd_path, node->argv, envp);
				perror("execve");
				exit(126);
			}
			exit(0);
		}
		else if (pid < 0)
		{
			perror("fork");
		}
	}
	else if (node->type == AST_PIPELINE)
	{
		execute_pipeline_recursive(node->left, pipes, cmd_index, total_cmds, shell);
		execute_pipeline_recursive(node->right, pipes, 
									cmd_index + count_commands_in_pipeline(node->left), 
									total_cmds, shell);
	}
}

int	execute_pipeline(t_ast *ast, t_shell *shell)
{
	int		total_cmds;
	int		**pipes;
	int		i;
	int		status;
	int		last_status;

	total_cmds = count_commands_in_pipeline(ast);
	if (total_cmds == 1)
		return (execute_command(ast, shell));
	
	pipes = malloc(sizeof(int *) * (total_cmds - 1));
	if (!pipes)
		return (1);
		
	for (i = 0; i < total_cmds - 1; i++)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (1);
		}
	}
	
	execute_pipeline_recursive(ast, pipes, 0, total_cmds, shell);
	
	for (i = 0; i < total_cmds - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
	
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

int	execute_ast(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return (0);
		
	if (ast->type == AST_COMMAND)
		return (execute_command(ast, shell));
	else if (ast->type == AST_PIPELINE)
		return (execute_pipeline(ast, shell));
	else if (ast->type == AST_AND)
	{
		shell->last_status = execute_ast(ast->left, shell);
		if (shell->last_status == 0)
			return (execute_ast(ast->right, shell));
		return (shell->last_status);
	}
	else if (ast->type == AST_OR)
	{
		shell->last_status = execute_ast(ast->left, shell);
		if (shell->last_status != 0)
			return (execute_ast(ast->right, shell));
		return (shell->last_status);
	}
	return (1);
}