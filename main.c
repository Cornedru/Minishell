/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 04:34:48 by ndehmej          ###   ########.fr       */
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

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	check_signal_status(void)
{
	int	status;

	status = g_signal_status;
	g_signal_status = SIG_NONE;
	return (status);
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

static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_ast	*ast;
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
	tokens = lexer(line);
	if (!tokens)
	{
		free(line);
		return ;
	}
	expand_tokens(tokens, shell);
	ast = parse(&tokens);
	free_tokens(tokens);
	if (!ast)
	{
		printf("Parse error\n");
		shell->last_status = 2;
		free(line);
		return ;
	}
	status = execute_ast(ast, shell);
	shell->last_status = status;
	free_ast(ast);
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