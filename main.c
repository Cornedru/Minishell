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

static void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	check_signal_status(void)
{
	int	status;

	status = g_signal_status;
	g_signal_status = SIG_NONE;
	return (status);
}

t_token	*lexer(char *input)
{
	(void)input;
	return (NULL);
}

t_ast	*parse(t_token **tokens)
{
	(void)tokens;
	return (NULL);
}

void	free_tokens(t_token *tokens)
{
	(void)tokens;
}

void	free_ast(t_ast *ast)
{
	(void)ast;
}

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	(void)tokens;
	(void)shell;
}

int	check_quotes(char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[i] == '"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

int	execute_command(t_ast *ast, t_shell *shell)
{
	(void)ast;
	(void)shell;
	printf("TODO: Execute command\n");
	return (0);
}

int	execute_pipeline(t_ast *ast, t_shell *shell)
{
	(void)ast;
	(void)shell;
	printf("TODO: Execute pipeline\n");
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (strcmp(cmd, "echo") == 0 || strcmp(cmd, "cd") == 0 || strcmp(cmd,
			"pwd") == 0 || strcmp(cmd, "export") == 0 || strcmp(cmd,
			"unset") == 0 || strcmp(cmd, "env") == 0 || strcmp(cmd,
			"exit") == 0)
		return (1);
	return (0);
}

char	*get_env_value(char *key, t_shell *shell)
{
	(void)key;
	(void)shell;
	return (NULL);
}

void	set_env_value(char *key, char *value, t_shell *shell)
{
	(void)key;
	(void)value;
	(void)shell;
}

void	cleanup_shell(t_shell *shell)
{
	(void)shell;
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (check_signal_status() == SIG_INTERRUPT)
		{
			shell->last_status = 130;
			continue ;
		}
		line = readline(PROMPT);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		printf("%s\n", line);
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

static void	init_shell(t_shell *shell)
{
	shell->env = NULL;
	shell->last_status = 0;
	shell->interactive = isatty(STDIN_FILENO);
	shell->cwd = getcwd(NULL, 0);
}

int	main(void)
{
	setup_signals();
	init_shell(&g_shell);
	shell_loop(&g_shell);
	cleanup_shell(&g_shell);
	return (0);
}
