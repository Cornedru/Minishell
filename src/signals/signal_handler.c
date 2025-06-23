/* signal_handler.c */
#include "minishell.h"

volatile sig_atomic_t	g_signal_status = SIG_NONE;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = SIG_INTERRUPT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_signal_status = SIG_QUIT;
		/* En mode interactif, ignorer SIGQUIT */
	}
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN); /* Ignorer en mode interactif */
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL); /* Comportement par défaut pour enfants */
	signal(SIGQUIT, SIG_DFL);
}

int	check_signal_status(void)
{
	int status = g_signal_status;
	g_signal_status = SIG_NONE;
	return (status);
}