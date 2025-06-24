/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 00:57:57 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = SIG_NONE;
t_shell					g_shell = {0};

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = SIG_INTERRUPT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	init_shell(t_shell *shell)
{
	shell->env = NULL;
	shell->last_status = 0;
	shell->interactive = isatty(STDIN_FILENO);
	shell->cwd = getcwd(NULL, 0);
	init_env(shell);
	if (!get_env_value("PWD", shell))
		set_env_value("PWD", shell->cwd, shell);
}

static int	execute_builtin_command(char **args, t_shell *shell)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, shell));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, shell));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, shell));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, shell));
	return (1);
}

static int	execute_external_command(char **args, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;
	pid_t	pid;
	int		status;

	cmd_path = find_command_path(args[0], shell);
	if (!cmd_path)
	{
		printf("%s: command not found\n", args[0]);
		return (127);
	}
	envp = env_to_array(shell->env);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(cmd_path, args, envp);
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
		ft_free_split(envp);
		return (WEXITSTATUS(status));
	}
	return (1);
}

static char	**parse_simple_command(char *line)
{
	char	**args;
	int		i;

	args = ft_split(line, ' ');
	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		char *unquoted = remove_quotes(args[i]);
		if (unquoted)
		{
			free(args[i]);
			args[i] = unquoted;
		}
		i++;
	}
	return (args);
}

static void	process_line(char *line, t_shell *shell)
{
	char	**args;
	int		status;

	if (*line == '\0')
	{
		free(line);
		return ;
	}
	if (check_quotes(line))
	{
		printf("Error: unclosed quotes\n");
		shell->last_status = 2;
		free(line);
		return ;
	}
	add_history(line);
	args = parse_simple_command(line);
	if (!args || !args[0])
	{
		ft_free_split(args);
		free(line);
		return ;
	}
	if (is_builtin(args[0]))
		status = execute_builtin_command(args, shell);
	else
		status = execute_external_command(args, shell);
	shell->last_status = status;
	ft_free_split(args);
	free(line);
}

static void	shell_loop(void)
{
	char	*line;

	while (1)
	{
		if (check_signal_status() == SIG_INTERRUPT)
		{
			g_shell.last_status = 130;
			continue ;
		}
		line = readline(PROMPT);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_line(line, &g_shell);
	}
}

int	main(void)
{
	setup_signals();
	init_shell(&g_shell);
	shell_loop();
	cleanup_shell(&g_shell);
	return (g_shell.last_status);
}