// #include "minishell.h"

// static void	print_prompt(void)
// {
// 	printf("minishell$ ");
// 	fflush(stdout);
// }

// static int	execute_ast(t_ast *ast, t_shell *shell)
// {
// 	if (!ast)
// 		return (0);
// 	switch (ast->type)
// 	{
// 	case AST_COMMAND:
// 		return (execute_command(ast, shell));
// 	case AST_PIPELINE:
// 		return (execute_pipeline(ast, shell));
// 	case AST_AND:
// 		shell->last_status = execute_ast(ast->left, shell);
// 		if (shell->last_status == 0)
// 			return (execute_ast(ast->right, shell));
// 		return (shell->last_status);
// 	case AST_OR:
// 		shell->last_status = execute_ast(ast->left, shell);
// 		if (shell->last_status != 0)
// 			return (execute_ast(ast->right, shell));
// 		return (shell->last_status);
// 	case AST_SUBSHELL:
// 		return (execute_ast(ast->left, shell));
// 	default:
// 		return (1);
// 	}
// }

// static void	shell_loop(t_shell *shell)
// {
// 	char	*line;
// 	t_token	*tokens;
// 	t_ast	*ast;
// 	int		sig_status;

// 	while (1)
// 	{
// 		sig_status = check_signal_status();
// 		if (sig_status == SIG_INTERRUPT)
// 		{
// 			shell->last_status = 130;
// 			continue ;
// 		}
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*line == '\0')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		if (check_quotes(line))
// 		{
// 			printf("minishell: syntax error: unmatched quotes\n");
// 			free(line);
// 			shell->last_status = 2;
// 			continue ;
// 		}
// 		tokens = lexer(line);
// 		free(line);
// 		if (!tokens)
// 			continue ;
// 		expand_tokens(tokens, shell);
// 		ast = parse(&tokens);
// 		free_tokens(tokens);
// 		if (!ast)
// 		{
// 			printf("minishell: syntax error\n");
// 			shell->last_status = 2;
// 			continue ;
// 		}
// 		shell->last_status = execute_ast(ast, shell);
// 		free_ast(ast);
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell shell;

// 	(void)argc;
// 	(void)argv;
// 	ft_memset(&shell, 0, sizeof(t_shell));
// 	shell.env = init_env(envp);
// 	shell.last_status = 0;
// 	shell.interactive = isatty(STDIN_FILENO);
// 	shell.cwd = getcwd(NULL, 0);
// 	setup_signals();
// 	shell_loop(&shell);
// 	cleanup_shell(&shell);
// 	return (shell.last_status);
// }