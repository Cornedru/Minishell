/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:00:00 by vous              #+#    #+#             */
/*   Updated: 2025/07/03 06:53:23 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal = 0;

t_sys	*init_sys(char **envp)
{
	t_sys	*sys;

	sys = (t_sys *)gc_malloc(sizeof(t_sys));
	sys->env_lst = pull_env(envp);
	sys->envp = dup_array(envp);
	sys->token = NULL;
	sys->ast = NULL;
	sys->exit = 0;
	return (sys);
}

// // Fonction pour afficher les tokens
// void	print_tokens(t_token *tokens)
// {
// 	t_token	*current;
// 	int		i;

// 	i = 0;
// 	current = tokens;
// 	printf("=== TOKENS ===\n");
// 	while (current)
// 	{
// 		printf("Token %d: Type=%d, Value='%s'\n", i, current->type, current->value);
// 		current = current->next;
// 		i++;
// 	}
// 	printf("\n");
// }

// // Fonction pour afficher l'AST
// void	print_ast(t_ast *node, int depth)
// {
// 	int	i;

// 	if (!node)
// 		return;
	
// 	// Indentation
// 	for (i = 0; i < depth; i++)
// 		printf("  ");
	
// 	// Afficher le type de nœud
// 	if (node->type == AST_CMD)
// 	{
// 		printf("CMD: ");
// 		if (node->args)
// 		{
// 			i = 0;
// 			while (node->args[i])
// 			{
// 				printf("'%s' ", node->args[i]);
// 				i++;
// 			}
// 		}
// 		printf("\n");
// 	}
// 	else if (node->type == AST_PIPE)
// 	{
// 		printf("PIPE\n");
// 		print_ast(node->left, depth + 1);
// 		print_ast(node->right, depth + 1);
// 	}
// 	else if (node->type == AST_AND)
// 	{
// 		printf("AND\n");
// 		print_ast(node->left, depth + 1);
// 		print_ast(node->right, depth + 1);
// 	}
// 	else if (node->type == AST_OR)
// 	{
// 		printf("OR\n");
// 		print_ast(node->left, depth + 1);
// 		print_ast(node->right, depth + 1);
// 	}
// }

// // Tests unitaires
// void	test_lexer(void)
// {
// 	t_token	*tokens;
// 	char	*tests[] = {
// 		"ls -la",
// 		"echo hello world",
// 		"ls | grep test",
// 		"cat < file.txt",
// 		"echo test > output.txt",
// 		"cmd1 && cmd2 || cmd3",
// 		"echo 'hello world'",
// 		"echo \"hello $USER\"",
// 		NULL
// 	};
// 	int		i;

// 	printf("\n=== TESTS LEXER ===\n");
// 	i = 0;
// 	while (tests[i])
// 	{
// 		printf("\nTest: '%s'\n", tests[i]);
// 		tokens = lexer(tests[i]);
// 		print_tokens(tokens);
// 		free_tokens(tokens);
// 		i++;
// 	}
// }

// void	test_parser(void)
// {
// 	t_token	*tokens;
// 	t_ast	*ast;
// 	char	*tests[] = {
// 		"ls -la",
// 		"echo hello world",
// 		"ls | grep test",
// 		"ls | grep test | wc -l",
// 		"cmd1 && cmd2",
// 		"cmd1 || cmd2",
// 		"cmd1 && cmd2 || cmd3",
// 		NULL
// 	};
// 	int		i;

// 	printf("\n=== TESTS PARSER ===\n");
// 	i = 0;
// 	while (tests[i])
// 	{
// 		printf("\nTest: '%s'\n", tests[i]);
// 		tokens = lexer(tests[i]);
// 		if (tokens)
// 		{
// 			ast = parse(&tokens);
// 			if (ast)
// 			{
// 				printf("AST:\n");
// 				print_ast(ast, 0);
// 				free_ast(ast);
// 			}
// 			else
// 				printf("Erreur de parsing\n");
// 			free_tokens(tokens);
// 		}
// 		i++;
// 	}
// }

// void	test_expander(t_sys *sys)
// {
// 	t_token	*tokens;
// 	// t_token	*current;
// 	char	*tests[] = {
// 		"echo $USER",
// 		"echo $HOME/test",
// 		"echo '$USER'",
// 		"echo \"$USER\"",
// 		"echo $?",
// 		"echo $$",
// 		"echo $NONEXISTENT",
// 		NULL
// 	};
// 	int		i;

// 	printf("\n=== TESTS EXPANDER ===\n");
	
// 	// Définir quelques variables pour les tests
// 	set_env_var(&sys->env_lst, "USER", "testuser");
// 	set_env_var(&sys->env_lst, "HOME", "/home/testuser");
// 	sys->exit_status = 42;
	
// 	i = 0;
// 	while (tests[i])
// 	{
// 		printf("\nTest: '%s'\n", tests[i]);
// 		tokens = lexer(tests[i]);
// 		if (tokens)
// 		{
// 			printf("Avant expansion:\n");
// 			print_tokens(tokens);
			
// 			expand_tokens(tokens, sys);
			
// 			printf("Après expansion:\n");
// 			print_tokens(tokens);
			
// 			free_tokens(tokens);
// 		}
// 		i++;
// 	}
// }

#include "minishell.h"

void	print_ast(t_ast *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("Node type: %d\n", node->type);

	if (node->args)
	{
		for (int i = 0; node->args[i]; i++)
		{
			for (int j = 0; j < level + 1; j++)
				printf("  ");
			printf("Arg: %s\n", node->args[i]);
		}
	}

	if (node->filename)
	{
		for (int i = 0; i < level + 1; i++)
			printf("  ");
		printf("File: %s\n", node->filename);
	}

	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token *tokens;
	t_ast	*ast;
	t_sys	*sys;

	(void)argc;
	(void)argv;

	sys = init_sys(envp);
	while (1)
	{
		input = readline("TEST_PARSE$ ");
		if (!input)
			break;

		if (check_quotes(input))
		{
			printf("Unmatched quotes!\n");
			continue;
		}

		tokens = lexer(input);
		expand_tokens(tokens, sys);
		ast = parse(&tokens);

		printf("=== AST Structure ===\n");
		print_ast(ast, 0);
		printf("=====================\n");

		free_tokens(tokens);
		free_ast(ast);
		free(input);
	}
	return (0);
}
