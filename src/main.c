/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/02 21:50:37 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int	handle_syntax_errors(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		// Check for syntax errors like starting with pipe, ending with pipe, etc.
		if (current == tokens && current->type == TOKEN_PIPE)
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		
		if (current->type == TOKEN_PIPE && current->next == NULL)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		
		if (current->type == TOKEN_PIPE && current->next && 
			current->next->type == TOKEN_PIPE)
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		
		if ((current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT ||
			current->type == TOKEN_REDIR_APPEND || current->type == TOKEN_HEREDOC) &&
			(!current->next || current->next->type != TOKEN_WORD))
		{
			if (current->next)
				printf("bash: syntax error near unexpected token `%s'\n", 
					current->next->value);
			else
				printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		
		current = current->next;
	}
	return (0);
}

static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_ast	*ast;
	int		status;

	if (!line || *line == '\0')
	{
		if (line)
			free(line);
		return ;
	}
	if (check_quotes(line))
	{
		printf("bash: syntax error: unclosed quotes\n");
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
	if (handle_syntax_errors(tokens))
	{
		shell->last_status = 2;
		free_tokens(tokens);
		free(line);
		return ;
	}
	expand_tokens(tokens, shell);
	ast = parse(&tokens);
	free_tokens(tokens);
	if (!ast)
	{
		printf("bash: parse error\n");
		shell->last_status = 2;
		free(line);
		return ;
	}
	status = execute_ast(ast, shell);
	shell->last_status = status;
	free_ast(ast);
	free(line);
}

static char	*get_prompt(void)
{
	return (readline(PROMPT));
}

static void	handle_eof(void)
{
	if (g_shell.interactive)
		printf("exit\n");
	cleanup_shell(&g_shell);
	exit(g_shell.last_status);
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
		line = get_prompt();
		if (!line)
		{
			handle_eof();
			break ;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		process_line(line, &g_shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	setup_signals();
	init_shell(&g_shell);
	
	char *shlvl = get_env_value("SHLVL", &g_shell);
	if (shlvl)
	{
		int level = ft_atoi(shlvl) + 1;
		char *new_shlvl = ft_itoa(level);
		set_env_value("SHLVL", new_shlvl, &g_shell);
		free(new_shlvl);
	}
	else
	{
		set_env_value("SHLVL", "1", &g_shell);
	}
	shell_loop();
	cleanup_shell(&g_shell);
	return (g_shell.last_status);
}