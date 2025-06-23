/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:40:04 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal_status;
extern t_shell					g_shell;

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

static void	setup_signals(void)
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
}

static void	process_line(char *line, t_shell *shell)
{
	(void) *shell;
	if (*line == '\0')
	{
		free(line);
		return ;
	}
	add_history(line);
	printf("%s\n", line);
	if (strcmp(line, "exit") == 0)
	{
		free(line);
		exit(0);
	}
	free(line);
}

int	main(void)
{
	char	*line;

	setup_signals();
	init_shell(&g_shell);
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
	cleanup_shell(&g_shell);
	return (0);
}