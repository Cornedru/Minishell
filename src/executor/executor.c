/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 23:46:18 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	char	*builtins[8];
	int		i;

	if (!cmd)
		return (0);
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

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				shell->last_status = 126;
				return (NULL);
			}
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			shell->last_status = 126;
			return (NULL);
		}
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

// static int	setup_single_redirection(t_redir *current)
// {
// 	int	fd;

// 	if (current->type == TOKEN_REDIR_IN)
// 	{
// 		fd = open(current->file, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror(current->file);
// 			return (-1);
// 		}
// 		if (dup2(fd, STDIN_FILENO) == -1)
// 		{
// 			close(fd);
// 			return (-1);
// 		}
// 		close(fd);
// 	}
// 	else if (current->type == TOKEN_REDIR_OUT)
// 	{
// 		fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 		{
// 			perror(current->file);
// 			return (-1);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) == -1)
// 		{
// 			close(fd);
// 			return (-1);
// 		}
// 		close(fd);
// 	}
// 	else if (current->type == TOKEN_REDIR_APPEND)
// 	{
// 		fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 		{
// 			perror(current->file);
// 			return (-1);
// 		}
// 		if (dup2(fd, STDOUT_FILENO) == -1)
// 		{
// 			close(fd);
// 			return (-1);
// 		}
// 		close(fd);
// 	}
// 	else if (current->type == TOKEN_HEREDOC)
// 	{
// 		if (handle_heredoc(current) == -1)
// 			return (-1);
// 	}
// 	return (0);
// }

static int	setup_single_redirection(t_redir *current)
{
	int	fd;

	if (!current || !current->file)
		return (-1);
		
	if (current->type == TOKEN_REDIR_IN)
	{
		fd = open(current->file, O_RDONLY);
		if (fd == -1)
		{
			perror(current->file);
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
			perror(current->file);
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
			perror(current->file);
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
	return (0);
}

static int	setup_redirections(t_redir *redirs)
{
	t_redir	*current;

	current = redirs;
	while (current)
	{
		if (setup_single_redirection(current) == -1)
			return (-1);
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

// static void	execute_external_command(char *cmd_path, t_ast *ast, t_shell *shell)
// {
// 	char	**envp;

// 	setup_child_signals();
// 	if (setup_redirections(ast->redirs) == -1)
// 		exit(1);
// 	envp = env_to_array(shell->env);
// 	execve(cmd_path, ast->argv, envp);
// 	perror("execve");
// 	exit(126);
// }

static void	execute_external_command(char *cmd_path, t_ast *ast, t_shell *shell)
{
	char	**envp;

	setup_child_signals();
	if (setup_redirections(ast->redirs) == -1)
		exit(1);
	
	// Add NULL check for env
	envp = env_to_array(shell->env);
	if (!envp)
	{
		// Create minimal environment if env_to_array fails
		envp = malloc(sizeof(char *) * 1);
		if (envp)
			envp[0] = NULL;
	}
	
	execve(cmd_path, ast->argv, envp);
	perror("execve");
	// Free envp on failure
	if (envp)
		ft_free_split(envp);
	exit(126);
}

int	execute_command(t_ast *ast, t_shell *shell)
{
	char	*cmd_path;
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
		ft_putstr_fd(ast->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	
	pid = fork();
	if (pid == 0)
		execute_external_command(cmd_path, ast, shell);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
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
		return (1);
	}
	return (0);
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