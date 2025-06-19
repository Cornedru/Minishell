#include "../libft/libft.h"
#include "../minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile sig_atomic_t	g_interrupted = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_interrupted = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	check_unmatched_quotes(const char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;
	int	stop;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	stop = 0;
	while (line[i])
	{
		if (line[i] == '\\' && !stop && !single_quote)
		{
			stop = 1;
			i++;
			continue ;
		}
		if (line[i] == '\'' && !double_quote && !stop)
			single_quote = !single_quote;
		else if (line[i] == '"' && !single_quote && !stop)
			double_quote = !double_quote;
		stop = 0;
		i++;
	}
	return (single_quote || double_quote);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	len1 = s1 ? strlen(s1) : 0;
	len2 = strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	if (s1)
		strcpy(new_str, s1);
	else
		new_str[0] = '\0';
	strcat(new_str, s2);
	free(s1);
	return (new_str);
}

char	*read_complete_line(void)
{
	char	*line;
	char	*tmp;

	line = NULL;
	g_interrupted = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (g_interrupted)
		{
			free(line);
			line = NULL;
			g_interrupted = 0;
			continue ;
		}
		if (!line)
			tmp = readline("MiniShell> ");
		else
			tmp = readline("> ");
		if (!tmp)
		{
			free(line);
			line = NULL;
			printf("exit\n");
			break ;
		}
		if (*tmp)
			add_history(tmp);
		if (line)
		{
			line = strjoin_free(line, tmp);
			free(tmp);
			break ;
		}
		else
		{
			line = tmp;
			break ;
		}
	}
	signal(SIGINT, SIG_DFL);
	return (line);
}
