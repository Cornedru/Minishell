// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test_parsing.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/03 00:00:00 by vous              #+#    #+#             */
// /*   Updated: 2025/07/06 06:47:49 by ndehmej          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// // // Fonction pour afficher les tokens
// // void	print_tokens(t_token *tokens)
// // {
// // 	t_token	*current;
// // 	int		i;

// // 	i = 0;
// // 	current = tokens;
// // 	printf("=== TOKENS ===\n");
// // 	while (current)
// // 	{
// // 		printf("Token %d: Type=%d, Value='%s'\n", i, current->type, current->value);
// // 		current = current->next;
// // 		i++;
// // 	}
// // 	printf("\n");
// // }

// // // Fonction pour afficher l'AST
// // void	print_ast(t_ast *node, int depth)
// // {
// // 	int	i;

// // 	if (!node)
// // 		return;
	
// // 	// Indentation
// // 	for (i = 0; i < depth; i++)
// // 		printf("  ");
	
// // 	// Afficher le type de nœud
// // 	if (node->type == AST_CMD)
// // 	{
// // 		printf("CMD: ");
// // 		if (node->args)
// // 		{
// // 			i = 0;
// // 			while (node->args[i])
// // 			{
// // 				printf("'%s' ", node->args[i]);
// // 				i++;
// // 			}
// // 		}
// // 		printf("\n");
// // 	}
// // 	else if (node->type == AST_PIPE)
// // 	{
// // 		printf("PIPE\n");
// // 		print_ast(node->left, depth + 1);
// // 		print_ast(node->right, depth + 1);
// // 	}
// // 	else if (node->type == AST_AND)
// // 	{
// // 		printf("AND\n");
// // 		print_ast(node->left, depth + 1);
// // 		print_ast(node->right, depth + 1);
// // 	}
// // 	else if (node->type == AST_OR)
// // 	{
// // 		printf("OR\n");
// // 		print_ast(node->left, depth + 1);
// // 		print_ast(node->right, depth + 1);
// // 	}
// // }

// // // Tests unitaires
// // void	test_lexer(void)
// // {
// // 	t_token	*tokens;
// // 	char	*tests[] = {
// // 		"ls -la",
// // 		"echo hello world",
// // 		"ls | grep test",
// // 		"cat < file.txt",
// // 		"echo test > output.txt",
// // 		"cmd1 && cmd2 || cmd3",
// // 		"echo 'hello world'",
// // 		"echo \"hello $USER\"",
// // 		NULL
// // 	};
// // 	int		i;

// // 	printf("\n=== TESTS LEXER ===\n");
// // 	i = 0;
// // 	while (tests[i])
// // 	{
// // 		printf("\nTest: '%s'\n", tests[i]);
// // 		tokens = lexer(tests[i]);
// // 		print_tokens(tokens);
// // 		free_tokens(tokens);
// // 		i++;
// // 	}
// // }

// // void	test_parser(void)
// // {
// // 	t_token	*tokens;
// // 	t_ast	*ast;
// // 	char	*tests[] = {
// // 		"ls -la",
// // 		"echo hello world",
// // 		"ls | grep test",
// // 		"ls | grep test | wc -l",
// // 		"cmd1 && cmd2",
// // 		"cmd1 || cmd2",
// // 		"cmd1 && cmd2 || cmd3",
// // 		NULL
// // 	};
// // 	int		i;

// // 	printf("\n=== TESTS PARSER ===\n");
// // 	i = 0;
// // 	while (tests[i])
// // 	{
// // 		printf("\nTest: '%s'\n", tests[i]);
// // 		tokens = lexer(tests[i]);
// // 		if (tokens)
// // 		{
// // 			ast = parse(&tokens);
// // 			if (ast)
// // 			{
// // 				printf("AST:\n");
// // 				print_ast(ast, 0);
// // 				free_ast(ast);
// // 			}
// // 			else
// // 				printf("Erreur de parsing\n");
// // 			free_tokens(tokens);
// // 		}
// // 		i++;
// // 	}
// // }

// // void	test_expander(t_sys *sys)
// // {
// // 	t_token	*tokens;
// // 	// t_token	*current;
// // 	char	*tests[] = {
// // 		"echo $USER",
// // 		"echo $HOME/test",
// // 		"echo '$USER'",
// // 		"echo \"$USER\"",
// // 		"echo $?",
// // 		"echo $$",
// // 		"echo $NONEXISTENT",
// // 		NULL
// // 	};
// // 	int		i;

// // 	printf("\n=== TESTS EXPANDER ===\n");
	
// // 	// Définir quelques variables pour les tests
// // 	set_env_var(&sys->env_lst, "USER", "testuser");
// // 	set_env_var(&sys->env_lst, "HOME", "/home/testuser");
// // 	sys->exit_status = 42;
	
// // 	i = 0;
// // 	while (tests[i])
// // 	{
// // 		printf("\nTest: '%s'\n", tests[i]);
// // 		tokens = lexer(tests[i]);
// // 		if (tokens)
// // 		{
// // 			printf("Avant expansion:\n");
// // 			print_tokens(tokens);
			
// // 			expand_tokens(tokens, sys);
			
// // 			printf("Après expansion:\n");
// // 			print_tokens(tokens);
			
// // 			free_tokens(tokens);
// // 		}
// // 		i++;
// // 	}
// // }

// // void	print_ast(t_ast *node, int level)
// // {
// // 	if (!node)
// // 		return;
// // 	for (int i = 0; i < level; i++)
// // 		printf("  ");
// // 	printf("Node type: %d\n", node->type);

// // 	if (node->args)
// // 	{
// // 		for (int i = 0; node->args[i]; i++)
// // 		{
// // 			for (int j = 0; j < level + 1; j++)
// // 				printf("  ");
// // 			printf("Arg: %s\n", node->args[i]);
// // 		}
// // 	}

// // 	if (node->filename)
// // 	{
// // 		for (int i = 0; i < level + 1; i++)
// // 			printf("  ");
// // 		printf("File: %s\n", node->filename);
// // 	}

// // 	print_ast(node->left, level + 1);
// // 	print_ast(node->right, level + 1);
// // }

// // int	main(int argc, char **argv, char **envp)
// // {
// // 	char	*input;
// // 	t_token *tokens;
// // 	t_ast	*ast;
// // 	t_sys	*sys;

// // 	(void)argc;
// // 	(void)argv;

// // 	sys = init_sys(envp);
// // 	while (1)
// // 	{
// // 		input = readline("TEST_PARSE$ ");
// // 		if (!input)
// // 			break;

// // 		if (check_quotes(input))
// // 		{
// // 			printf("Unmatched quotes!\n");
// // 			continue;
// // 		}

// // 		tokens = lexer(input);
// // 		expand_tokens(tokens, sys);
// // 		ast = parse(&tokens);

// // 		printf("=== AST Structure ===\n");
// // 		print_ast(ast, 0);
// // 		printf("=====================\n");

// // 		free_tokens(tokens);
// // 		free_ast(ast);
// // 		free(input);
// // 	}
// // 	return (0);
// // }

// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include "includes/minishell.h"

// // void print_ast(t_ast *ast);

// // void test_input(char *input)
// // {
// //     printf("=== TEST INPUT ===\n");
// //     printf("Input: %s\n", input);
// //     t_token *tokens = lexer(input);
// //     t_ast   *ast = parse(&tokens);   // <- ici

// //     printf("=== AST ===\n");
// //     print_ast(ast);
// //     printf("=====================\n");

// //     free_tokens(tokens);
// //     free_ast(ast);
// // }

// // int main(int argc, char **argv, char **envp)
// // {
// //     (void)argc;
// //     (void)argv;

// //     t_sys *sys = init_sys(envp);

// //     // Cas simples
// //     test_input("ls -la");
// //     test_input("echo Hello World");
// //     test_input("pwd");

// //     // Redirections
// //     test_input("cat < input.txt");
// //     test_input("echo 'hello' > file.txt");
// //     test_input("grep test < input.txt > output.txt");

// //     // Pipes
// //     test_input("ls -la | grep .c");
// //     test_input("cat file | sort | uniq");

// //     // Variables (en supposant expanseur actif)
// //     test_input("echo $HOME");
// //     test_input("echo \"$USER is logged in\"");

// //     // Quotes
// //     test_input("echo \"hello world\"");
// //     test_input("echo 'single quoted $VAR'");
// //     test_input("echo \"double quoted $VAR\"");

// //     // Mixed
// //     test_input("echo \"$USER\" | grep root > out.txt");
// //     test_input("cat < infile | grep \"pattern\" | sort > outfile");

// //     // Espaces, tabs, etc.
// //     test_input("    ls      -l     ");
// //     test_input("\techo\thello");

// //     // Syntaxe invalide (facultatif)
// //     test_input("cat <");
// //     test_input("echo | | ls");

// //     (void)sys; // si tu ne l'utilises pas pour éviter warning

// //     return 0;
// // }

// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <readline/readline.h>
// // #include <readline/history.h>
// // #include "includes/minishell.h"

// // const char *node_type_name(int type)
// // {
// //     if (type == 0) return "CMD";
// //     if (type == 1) return "PIPE";
// //     if (type == 6) return "AND";
// //     // ajoute tous tes types ici...
// //     return "UNKNOWN";
// // }

// // // Ton print_ast avec niveau indenté


// // // Fonction de test simple (pour appel dans suite)
// // void test_input(char *input, t_sys *sys)
// // {
// //     printf("=== TEST INPUT ===\n");
// //     printf("Input: %s\n", input);
// //     t_token *tokens = lexer(input);
// //     expand_tokens(tokens, sys);
// //     t_ast *ast = parse(&tokens);

// //     printf("=== AST Structure ===\n");
// //     print_ast(ast, 0);
// //     printf("=====================\n");

// //     free_tokens(tokens);
// //     free_ast(ast);
// // }

// // // Suite de tests complexes
// // void test_complex_suite(t_sys *sys)
// // {
// //     test_input("ls -la /tmp", sys);
// //     test_input("echo Hello World", sys);
// //     test_input("pwd", sys);

// //     test_input("cat < input.txt", sys);
// //     test_input("echo 'hello' > file.txt", sys);
// //     test_input("grep test < input.txt > output.txt", sys);

// //     test_input("ls -la | grep .c", sys);
// //     test_input("cat file | sort | uniq", sys);

// //     test_input("echo $HOME", sys);
// //     test_input("echo \"$USER is logged in\"", sys);
// //     test_input("echo '$USER will not expand'", sys);
// //     test_input("echo \"Mixing $SHELL and 'quotes'\"", sys);

// //     test_input("cat < infile | grep pattern > outfile", sys);
// //     test_input("echo \"multi\nline\" | grep line", sys);

// //     test_input("cat file1 | grep pattern > result.txt | sort", sys);

// //     test_input("echo \"She said \\\"Hello\\\"\"", sys);
// //     test_input("echo 'It\\'s a test'", sys);

// //     test_input("echo $UNDEFINED_VAR", sys);
// //     test_input("echo ${USER:-default}", sys);

// //     test_input("    ls\t-l  \t  /tmp  ", sys);
// //     test_input("echo \n Hello \n World", sys);

// //     test_input("cat <", sys);
// //     test_input("echo | | ls", sys);
// //     test_input("grep 'unclosed_quote", sys);
// //     test_input("echo \"unclosed double quote", sys);

// //     test_input("echo append >> file.txt", sys);
// //     test_input("cat file.txt >> output.txt", sys);

// //     test_input("cd /tmp && ls | grep file", sys);

// //     test_input("find / -type f | grep minishell | sort | uniq > result.log", sys);

// //     test_input("echo \"A 'nested' quote\"", sys);
// //     test_input("echo 'A \"nested\" quote'", sys);

// //     test_input("echo      multiple      spaces", sys);
// //     test_input("echo\tmixed\tspaces\tand\ttabs", sys);
// // }

// // int main(int argc, char **argv, char **envp)
// // {
// //     (void)argc;
// //     (void)argv;

// //     t_sys *sys = init_sys(envp);

// //     // Lancer la suite de tests complexes au démarrage
// //     printf("==== Lancement de la suite de tests complexes ====\n");
// //     test_complex_suite(sys);
// //     printf("==== Fin des tests ====\n\n");

// //     // Boucle REPL interactive
// //     while (1)
// //     {
// //         char *input = readline("TEST_PARSE$ ");
// //         if (!input)
// //             break;

// //         if (check_quotes(input))
// //         {
// //             printf("Unmatched quotes!\n");
// //             free(input);
// //             continue;
// //         }

// //         t_token *tokens = lexer(input);
// //         expand_tokens(tokens, sys);
// //         t_ast *ast = parse(&tokens);

// //         printf("=== AST Structure ===\n");
// //         print_ast(ast, 0);
// //         printf("=====================\n");

// //         free_tokens(tokens);
// //         free_ast(ast);
// //         free(input);
// //     }

// //     return 0;
// // }

// // #include "../includes/minishell.h"
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>
// // #include <sys/wait.h>

// // volatile sig_atomic_t g_signal = 0;

// // t_sys	*init_sys(char **envp)
// // {
// // 	t_sys	*sys;

// // 	sys = (t_sys *)gc_malloc(sizeof(t_sys));
// // 	sys->env_lst = pull_env(envp);
// // 	sys->envp = dup_array(envp);
// // 	sys->token = NULL;
// // 	sys->ast = NULL;
// // 	sys->exit = 0;
// // 	return (sys);
// // }


// // void print_ast(t_ast *node, int level)
// // {
// //     if (!node)
// //         return;
// //     for (int i = 0; i < level; i++)
// //         printf("  ");
// //     printf("Node type: %d\n", node->type);

// //     if (node->args)
// //     {
// //         for (int i = 0; node->args[i]; i++)
// //         {
// //             for (int j = 0; j < level + 1; j++)
// //                 printf("  ");
// //             printf("Arg: %s\n", node->args[i]);
// //         }
// //     }

// //     if (node->filename)
// //     {
// //         for (int i = 0; i < level + 1; i++)
// //             printf("  ");
// //         printf("File: %s\n", node->filename);
// //     }

// //     print_ast(node->left, level + 1);
// //     print_ast(node->right, level + 1);
// // }

// // int check_bash_syntax(const char *cmd)
// // {
// //     int status;
// //     pid_t pid = fork();
// //     if (pid == 0) {
// //         // Fils : exécute bash -n
// //         execlp("bash", "bash", "-n", "-c", cmd, NULL);
// //         _exit(127); // en cas d’erreur execlp
// //     } else if (pid > 0) {
// //         waitpid(pid, &status, 0);
// //         if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
// //             return 1; // syntax OK
// //         else
// //             return 0; // syntax error
// //     }
// //     return 0; // erreur fork
// // }

// // void test_and_compare(char *input, t_sys *sys)
// // {
// //     printf("=== TEST INPUT ===\nInput: %s\n", input);
// //     if (!check_bash_syntax(input))
// //     {
// //         printf("Bash détecte une erreur de syntaxe.\n");
// //     }
// //     else
// //     {
// //         t_token *tokens = lexer(input);
// //         if (!tokens)
// //         {
// //             printf("Lexer a échoué.\n");
// //             return;
// //         }
// //         expand_tokens(tokens, sys);
// //         t_ast *ast = parse(&tokens);
// //         if (!ast)
// //         {
// //             printf("Parser a échoué.\n");
// //         }
// //         else
// //         {
// //             printf("AST généré:\n");
// //             print_ast(ast, 0);
// //             free_ast(ast);
// //         }
// //         free_tokens(tokens);
// //     }
// //     printf("=====================\n\n");
// // }

// // int main(int argc, char **argv, char **envp)
// // {
// //     t_sys *sys = init_sys(envp);
// // 	(void)argc;
// // 	(void)argv;

// //     // Liste de tests à faire
// //     char *tests[] = {
// //         "ls -la /tmp",
// //         "echo Hello World",
// //         "cat < input.txt",
// //         "echo 'hello' > file.txt",
// //         "grep test < input.txt > output.txt",
// //         "ls -la | grep .c",
// //         "cat file | sort | uniq",
// //         "echo $HOME",
// //         "echo 'unmatched quote",
// //         "echo | | ls",
// //         NULL
// //     };

// //     for (int i = 0; tests[i]; i++)
// //         test_and_compare(tests[i], sys);

// //     return 0;
// // }


// // #include "../includes/minishell.h"
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <unistd.h>
// // #include <sys/wait.h>

// // volatile sig_atomic_t g_signal = 0;

// // void free_sys(t_sys *sys)
// // {
// //     if (!sys)
// //         return;
// //     free_env_list(sys->env_lst);  // ta fonction d'environnements
// //     free_array(sys->envp);        // ta fonction pour tableau de strings
// //     free_tokens(sys->token);
// //     free_ast(sys->ast);
// //     free(sys);
// // }

// // t_sys *init_sys(char **envp)
// // {
// //     t_sys *sys;

// //     sys = (t_sys *)gc_malloc(sizeof(t_sys));
// //     sys->env_lst = pull_env(envp);
// //     sys->envp = dup_array(envp);
// //     sys->token = NULL;
// //     sys->ast = NULL;
// //     sys->exit = 0;
// //     return (sys);
// // }

// // void print_ast_line(t_ast *node)
// // {
// //     if (!node)
// //         return;
// //     printf("Type:%d Args:", node->type);
// //     if (node->args)
// //     {
// //         for (int i = 0; node->args[i]; i++)
// //             printf("%s,", node->args[i]);
// //     }
// //     printf("\n");
// //     if (node->left)
// //         print_ast_line(node->left);
// //     if (node->right)
// //         print_ast_line(node->right);
// // }

// // int check_bash_syntax(const char *cmd)
// // {
// //     int status;
// //     pid_t pid = fork();

// //     if (pid == 0)
// //     {
// //         // Fils : exécute bash -n (check syntax)
// //         execlp("bash", "bash", "-n", "-c", cmd, NULL);
// //         _exit(127); // erreur execlp
// //     }
// //     else if (pid > 0)
// //     {
// //         waitpid(pid, &status, 0);
// //         if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
// //             return 1; // syntax OK
// //         else
// //             return 0; // syntax error
// //     }
// //     return 0; // fork error
// // }

// // void test_and_compare(char *input, t_sys *sys)
// // {
// //     printf("=== TEST INPUT ===\nInput: %s\n", input);
// //     int bash_ok = check_bash_syntax(input);

// //     t_token *tokens = NULL;
// //     t_ast *ast = NULL;

// //     if (!bash_ok)
// //     {
// //         printf("Bash détecte une erreur de syntaxe.\n");
// //     }

// //     tokens = lexer(input);
// //     if (!tokens)
// //     {
// //         printf("Lexer a échoué.\n");
// //     }
// //     else
// //     {
// //         expand_tokens(tokens, sys);
// //         ast = parse(&tokens);
// //     }

// //     if (bash_ok && ast)
// //     {
// //         printf("AST généré:\n");
// //         print_ast_line(ast);
// //         printf("Test OK: syntaxe valide et AST généré.\n");
// //     }
// //     else if (!bash_ok && !ast)
// //     {
// //         printf("Test OK: erreur de syntaxe détectée par bash et minishell.\n");
// //     }
// //     else
// //     {
// //         printf("Discrepance détectée !\n");
// //         if (!bash_ok)
// //             printf("Bash détecte une erreur, mais minishell a généré un AST.\n");
// //         else
// //             printf("Bash valide la syntaxe, mais minishell n'a pas généré d'AST.\n");
// //     }

// //     if (ast)
// //         free_ast(ast);
// //     if (tokens)
// //         free_tokens(tokens);

// //     printf("=====================\n\n");
// // }

// // int main(int argc, char **argv, char **envp)
// // {
// //     t_sys *sys = init_sys(envp);
// //     (void)argc;
// //     (void)argv;

// //     char *tests[] = {
// //         "ls -la /tmp",
// //         "echo Hello World",
// //         "cat < input.txt",
// //         "echo 'hello' > file.txt",
// //         "grep test < input.txt > output.txt",
// //         "ls -la | grep .c",
// //         "cat file | sort | uniq",
// //         "echo $HOME",
// //         "echo 'unmatched quote",
// //         "echo | | ls",
// //         NULL};

// //     for (int i = 0; tests[i]; i++)
// //         test_and_compare(tests[i], sys);

// //     // À la fin, libérer sys et son contenu si nécessaire
// // 	free_sys(sys);

// //     return 0;
// // }


// // #include "../includes/minishell.h"
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <unistd.h>
// // #include <sys/wait.h>

// // volatile sig_atomic_t g_signal = 0;



// // t_sys *init_sys(char **envp)
// // {
// //     t_sys *sys;

// //     sys = (t_sys *)gc_malloc(sizeof(t_sys));
// //     sys->env_lst = pull_env(envp);
// //     sys->envp = dup_array(envp);
// //     sys->token = NULL;
// //     sys->ast = NULL;
// //     sys->exit = 0;
// //     return (sys);
// // }

// // void print_ast_line(t_ast *node)
// // {
// //     if (!node)
// //         return;
// //     printf("Type:%d Args:", node->type);
// //     if (node->args)
// //     {
// //         for (int i = 0; node->args[i]; i++)
// //             printf("%s,", node->args[i]);
// //     }
// //     printf("\n");
// //     if (node->left)
// //         print_ast_line(node->left);
// //     if (node->right)
// //         print_ast_line(node->right);
// // }

// // int check_bash_syntax(const char *cmd)
// // {
// //     int status;
// //     pid_t pid = fork();

// //     if (pid == 0)
// //     {
// //         // Fils : exécute bash -n (check syntax)
// //         execlp("bash", "bash", "-n", "-c", cmd, NULL);
// //         _exit(127); // erreur execlp
// //     }
// //     else if (pid > 0)
// //     {
// //         waitpid(pid, &status, 0);
// //         if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
// //             return 1; // syntax OK
// //         else
// //             return 0; // syntax error detected by bash
// //     }
// //     return 0; // fork error
// // }

// // void test_and_compare(char *input, t_sys *sys)
// // {
// //     printf("=== TEST INPUT ===\nInput: %s\n", input);
// //     int bash_detected_syntax_ok = check_bash_syntax(input);
// //     int bash_detected_syntax_error = !bash_detected_syntax_ok;

// //     t_token *tokens = NULL;
// //     t_ast *ast = NULL;

// //     tokens = lexer(input);
// //     if (!tokens)
// //     {
// //         printf("Lexer a échoué.\n");
// //     }
// //     else
// //     {
// //         expand_tokens(tokens, sys);
// //         ast = parse(&tokens);
// //     }

// //     if (!ast)
// //     {
// //         if (bash_detected_syntax_error)
// //             printf("Test OK: erreur syntaxe détectée par bash et minishell.\n");
// //         else
// //             printf("Parser a échoué mais bash n’a pas détecté d’erreur.\n");
// //     }
// //     else
// //     {
// //         if (!bash_detected_syntax_error)
// //         {
// //             printf("AST généré:\n");
// //             print_ast_line(ast);
// //             printf("Test OK: syntaxe valide et AST généré.\n");
// //         }
// //         else
// //         {
// //             printf("Discrepance détectée ! Bash détecte une erreur, mais minishell a généré un AST.\n");
// //             printf("AST généré (potentiellement incorrect):\n");
// //             print_ast_line(ast);
// //         }
// //         free_ast(ast);
// //     }

// //     if (tokens)
// //         free_tokens(tokens);

// //     printf("=====================\n\n");
// // }


// // // Dans utils.c
// // #include "gc.h" // pour gc_free_array
// // #include <stdlib.h>

// // void free_env_list(t_env *env_lst)
// // {
// //     t_env *tmp;

// //     while (env_lst)
// //     {
// //         tmp = env_lst->next;
// //         free(env_lst->var);
// //         free(env_lst->content);
// //         free(env_lst);
// //         env_lst = tmp;
// //     }
// // }

// // void free_sys(t_sys *sys)
// // {
// //     if (!sys)
// //         return;

// //     free_env_list(sys->env_lst);

// //     if (sys->envp)
// //         gc_free_array((void **)sys->envp);  // Ton tableau de char*

// //     // Pour token et ast, on les libère ailleurs, donc ici on ne les libère pas

// //     free(sys);
// // }


// // int main(int argc, char **argv, char **envp)
// // {
// //     t_sys *sys = init_sys(envp);
// //     (void)argc;
// //     (void)argv;

// //     char *tests[] = {
// //         "ls -la /tmp",
// //         "echo Hello World",
// //         "cat < input.txt",
// //         "echo 'hello' > file.txt",
// //         "grep test < input.txt > output.txt",
// //         "ls -la | grep .c",
// //         "cat file | sort | uniq",
// //         "echo $HOME",
// //         "echo 'unmatched quote",
// //         "echo | | ls",
// //         NULL};

// //     for (int i = 0; tests[i]; i++)
// //     {
// //         test_and_compare(tests[i], sys);
// //     }

// //     free_sys(sys);

// //     return 0;
// // }


// // #include "../includes/minishell.h"
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <unistd.h>

// // volatile sig_atomic_t g_signal = 0;

// // t_sys *init_sys(char **envp)
// // {
// // 	t_sys *sys = (t_sys *)gc_malloc(sizeof(t_sys));
// // 	sys->env_lst = pull_env(envp);
// // 	sys->envp = dup_array(envp);
// // 	sys->token = NULL;
// // 	sys->ast = NULL;
// // 	sys->exit = 0;
// // 	return sys;
// // }

// // // Fonction récursive pour afficher l'AST avec indentation
// // void print_ast(t_ast *node, int depth)
// // {
// // 	if (!node)
// // 		return;

// // 	for (int i = 0; i < depth; i++)
// // 		printf("  ");

// // 	printf("Node Type: %d\n", node->type);

// // 	if (node->args)
// // 	{
// // 		for (int i = 0; node->args[i]; i++)
// // 		{
// // 			for (int j = 0; j < depth + 1; j++)
// // 				printf("  ");
// // 			printf("Arg[%d]: %s\n", i, node->args[i]);
// // 		}
// // 	}

// // 	if (node->filename)
// // 	{
// // 		for (int j = 0; j < depth + 1; j++)
// // 			printf("  ");
// // 		printf("File: %s\n", node->filename);
// // 	}

// // 	if (node->left)
// // 	{
// // 		for (int i = 0; i < depth; i++)
// // 			printf("  ");
// // 		printf("Left:\n");
// // 		print_ast(node->left, depth + 1);
// // 	}

// // 	if (node->right)
// // 	{
// // 		for (int i = 0; i < depth; i++)
// // 			printf("  ");
// // 		printf("Right:\n");
// // 		print_ast(node->right, depth + 1);
// // 	}
// // }

// // int main(int argc, char **argv, char **envp)
// // {
// // 	(void)argc;
// // 	(void)argv;

// // 	t_sys *sys = init_sys(envp);

// // 	char *inputs[] = {
// // 		"ls -la",
// // 		"echo Hello World",
// // 		"cat < infile",
// // 		"echo test > outfile",
// // 		"ls | grep .c",
// // 		"cat file | sort | uniq",
// // 		"false && echo fail",
// // 		"true || echo fallback",
// // 		"echo start && ls | wc -l > result.txt",
// // 		NULL
// // 	};

// // 	for (int i = 0; inputs[i]; i++)
// // 	{
// // 		printf("\n========== TEST %d ==========\n", i + 1);
// // 		printf("Input: %s\n", inputs[i]);

// // 		t_token *tokens = lexer(inputs[i]);
// // 		if (!tokens)
// // 		{
// // 			printf("Lexer failed.\n");
// // 			continue;
// // 		}

// // 		expand_tokens(tokens, sys);

// // 		t_ast *ast = parse(&tokens);
// // 		if (!ast)
// // 		{
// // 			printf("Parser failed.\n");
// // 		}
// // 		else
// // 		{
// // 			printf("AST:\n");
// // 			print_ast(ast, 0);
// // 		}

// // 		free_tokens(tokens);
// // 		free_ast(ast);
// // 	}

// // 	return 0;
// // }


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: assistant                                      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/02 21:34:42 by oligrien          #+#    #+#             */
// /*   Updated: 2025/07/06                               ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// volatile sig_atomic_t g_signal = 0;


// void print_ast(t_ast *node, int level)
// {
//     if (!node)
//         return;
//     for (int i = 0; i < level; i++)
//         printf("  ");
//     printf("Node type: %d\n", node->type);

//     if (node->args)
//     {
//         for (int i = 0; node->args[i]; i++)
//         {
//             for (int j = 0; j < level + 1; j++)
//                 printf("  ");
//             printf("Arg: %s\n", node->args[i]);
//         }
//     }

//     if (node->filename)
//     {
//         for (int i = 0; i < level + 1; i++)
//             printf("  ");
//         printf("File: %s\n", node->filename);
//     }

//     print_ast(node->left, level + 1);
//     print_ast(node->right, level + 1);
// }

// // Creates a simple command node (a leaf of the tree)
// t_ast	*create_cmd_node(char **args)
// {
// 	t_ast	*node;

// 	node = (t_ast *)gc_malloc(sizeof(t_ast));
// 	node->type = AST_CMD;
// 	node->args = args; // The args array must also be from the GC
// 	node->filename = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // Creates an operator node (pipe, and, or)
// t_ast	*create_op_node(t_ast_type type, t_ast *left, t_ast *right)
// {
// 	t_ast	*node;

// 	node = (t_ast *)gc_malloc(sizeof(t_ast));
// 	node->type = type;
// 	node->args = NULL;
// 	node->filename = NULL;
// 	node->left = left;
// 	node->right = right;
// 	return (node);
// }

// // Creates a redirection node
// t_ast	*create_redir_node(t_ast_type type, char *filename, t_ast *cmd_node)
// {
// 	t_ast	*node;

// 	node = (t_ast *)gc_malloc(sizeof(t_ast));
// 	node->type = type;
// 	node->args = NULL;
// 	node->filename = filename; // The filename string must be from the GC
// 	node->left = cmd_node;
// 	node->right = NULL;
// 	return (node);
// }

// // ls -l
// t_ast	*mock_ls_command(void)
// {
// 	char	**ls_args;

// 	// The array of arguments MUST be NULL-terminated.
// 	ls_args = (char **)gc_malloc(sizeof(char *) * 3);
// 	ls_args[0] = gc_strdup("ls");
// 	ls_args[1] = gc_strdup("-l");
// 	ls_args[2] = NULL;

// 	return (create_cmd_node(ls_args));
// }

// // cat < input.txt
// t_ast	*mock_redir_command(void)
// {
// 	t_ast	*cmd_node;
// 	char	**cat_args;
	
// 	cat_args = (char **)gc_malloc(sizeof(char *) * 2);
// 	cat_args[0] = gc_strdup("cat");
// 	cat_args[1] = NULL;
// 	cmd_node = create_cmd_node(cat_args);
	
// 	// The redirection node wraps the command node.
// 	return (create_redir_node(AST_REDIR_IN, gc_strdup("input.txt"), cmd_node));
// }

// // ls -l | grep ".c"
// t_ast	*mock_pipe_command(void)
// {
// 	t_ast	*ls_node;
// 	t_ast	*grep_node;
// 	char	**ls_args;
// 	char	**grep_args;

// 	// Left side of the pipe
// 	ls_args = (char **)gc_malloc(sizeof(char *) * 3);
// 	ls_args[0] = gc_strdup("ls");
// 	ls_args[1] = gc_strdup("-l");
// 	ls_args[2] = NULL;
// 	ls_node = create_cmd_node(ls_args);

// 	// Right side of the pipe
// 	grep_args = (char **)gc_malloc(sizeof(char *) * 3);
// 	grep_args[0] = gc_strdup("grep");
// 	grep_args[1] = gc_strdup(".c");
// 	grep_args[2] = NULL;
// 	grep_node = create_cmd_node(grep_args);

// 	// The pipe node connects them.
// 	return (create_op_node(AST_PIPE, ls_node, grep_node));
// }

// void run_parsing_tests(void)
// {
//     printf("Running parsing tests...\n");
    
//     // Your testing code here
//     // For example: test_lexer(); test_parser(); etc.
    
//     printf("Parsing tests completed.\n");
// }

// /**
//  * init_sys - Initialise la structure système
//  */
// t_sys	*init_sys(char **envp)
// {
// 	t_sys	*sys;

// 	sys = (t_sys *)gc_malloc(sizeof(t_sys));
// 	if (!sys)
// 		return (NULL);
// 	sys->env_lst = pull_env(envp);
// 	sys->envp = dup_array(envp);
// 	sys->token = NULL;
// 	sys->ast = NULL;
// 	sys->exit = 0;
// 	sys->exit_status = 0;
// 	return (sys);
// }

// /**
//  * setup_signals - Configure les gestionnaires de signaux
//  */


// /**
//  * process_line - Traite une ligne de commande
//  */
// int	process_line(char *line, t_sys *sys)
// {
// 	t_ast	*ast;
// 	int		status;

// 	// Parser la ligne
// 	ast = parse_line(line, sys);
// 	if (!ast)
// 	{
// 		sys->exit_status = 2; // Erreur de syntaxe
// 		return (2);
// 	}

// 	// Debug: afficher l'AST si demandé
// 	if (getenv("DEBUG_AST"))
// 	{
// 		ft_putstr_fd("=== AST ===\n", 1);
// 		print_ast(ast, 0);
// 		ft_putstr_fd("===========\n", 1);
// 	}

// 	// Exécuter l'AST
// 	status = execute(ast, sys);
// 	sys->exit_status = status;

// 	// Nettoyer
// 	free_ast(ast);

// 	return (status);
// }

// /**
//  * check_builtin_exit - Vérifie si la commande est "exit"
//  */
// int	check_builtin_exit(char *line, t_sys *sys)
// {
// 	char	**args;
// 	int		i;

// 	// Simple vérification pour "exit"
// 	args = gc_split(line, ' ');
// 	if (!args || !args[0])
// 		return (0);

// 	if (ft_strcmp(args[0], "exit") == 0)
// 	{
// 		ft_putstr_fd("exit\n", 1);
// 		sys->exit = 1;
		
// 		// Si un argument est fourni, l'utiliser comme code de sortie
// 		if (args[1] && ft_strlen(args[1]) > 0)
// 		{
// 			i = 0;
// 			while (args[1][i])
// 			{
// 				if (!ft_isdigit(args[1][i]) && args[1][i] != '-' && args[1][i] != '+')
// 				{
// 					ft_putstr_fd("minishell: exit: ", 2);
// 					ft_putstr_fd(args[1], 2);
// 					ft_putstr_fd(": numeric argument required\n", 2);
// 					sys->exit_status = 255;
// 					gc_free_array((void **)args);
// 					return (1);
// 				}
// 				i++;
// 			}
// 			sys->exit_status = ft_atoi(args[1]) % 256;
// 		}
		
// 		gc_free_array((void **)args);
// 		return (1);
// 	}

// 	gc_free_array((void **)args);
// 	return (0);
// }

// /**
//  * read_line - Boucle principale de lecture des commandes
//  */
// int	read_line(t_sys *sys)
// {
// 	char	*line;

// 	while (!sys->exit)
// 	{
// 		// Afficher le prompt et lire une ligne
// 		line = readline(PROMPT);
		
// 		// EOF (Ctrl+D)
// 		if (!line)
// 		{
// 			ft_putstr_fd("exit\n", 1);
// 			break;
// 		}

// 		// Ligne vide
// 		if (ft_strlen(line) == 0)
// 		{
// 			free(line);
// 			continue;
// 		}

// 		// Ajouter à l'historique
// 		add_history(line);

// 		// Vérifier si c'est "exit"
// 		if (check_builtin_exit(line, sys))
// 		{
// 			free(line);
// 			break;
// 		}

// 		// Traiter la commande
// 		process_line(line, sys);

// 		// Libérer la ligne
// 		free(line);
// 	}

// 	return (sys->exit_status);
// }

// /**
//  * cleanup - Nettoie toutes les ressources
//  */


// // /**
// //  * main - Point d'entrée principal
// //  */
// // int	main(int argc, char **argv, char **envp)
// // {
// // 	t_sys	*sys;
// // 	int		exit_status;

// // 	// Mode test si --test est passé
// // 	if (argc > 1 && ft_strcmp(argv[1], "--test") == 0)
// // 	{
// // 		run_parsing_tests();
// // 		return (0);
// // 	}

// // 	// Mode debug AST si --debug-ast est passé
// // 	if (argc > 1 && ft_strcmp(argv[1], "--debug-ast") == 0)
// // 		setenv("DEBUG_AST", "1", 1);

// // 	// Initialiser le système
// // 	sys = init_sys(envp);
// // 	if (!sys)
// // 	{
// // 		ft_putstr_fd("minishell: failed to initialize\n", 2);
// // 		return (1);
// // 	}

// // 	// Configurer les signaux
// // 	setup_signals();

// // 	// Message de bienvenue (optionnel)
// // 	if (isatty(STDIN_FILENO))
// // 	{
// // 		ft_putstr_fd("minishell v1.0\n", 1);
// // 		ft_putstr_fd("Type 'exit' to quit\n", 1);
// // 	}

// // 	// Boucle principale
// // 	exit_status = read_line(sys);

// // 	// Nettoyer
// // 	cleanup(sys);

// // 	return (exit_status);
// // }


// // #include "../includes/minishell.h"

// // void test_parse_line(t_sys *sys, const char *line)
// // {
// //     printf("Parsing line: %s\n", line);

// //     t_ast *ast = parse_line((char *)line, sys);
// //     if (!ast)
// //     {
// //         printf("Parsing failed or returned NULL\n");
// //         return;
// //     }

// //     print_ast(ast, 0);
// //     free_ast(ast);
// // }

// // int main(int argc, char **argv, char **envp)
// // {
// //     t_sys *sys;
// // 	(void)argc;
// // 	(void)argv;
// //     // int exit_status;

// //     // Initialisation du système (environnement, etc.)
// //     sys = init_sys(envp);
// //     if (!sys)
// //     {
// //         ft_putstr_fd("minishell: failed to initialize\n", 2);
// //         return (1);
// //     }

// //     // Configuration des signaux (ici on ignore Ctrl+C et Ctrl+\ pour test)
// //     setup_signals();

// //     // Message d’accueil si l’entrée est un terminal
// //     if (isatty(STDIN_FILENO))
// //     {
// //         ft_putstr_fd("minishell v1.0 - Test Parser\n", 1);
// //     }

// //     // Tests simples du parser AST avec plusieurs commandes
// //     test_parse_line(sys, "ls -l");
// //     test_parse_line(sys, "cat < input.txt");
// //     test_parse_line(sys, "ls -l | grep \".c\"");
// //     test_parse_line(sys, "echo 'hello world'");

// //     // Nettoyage
// //     cleanup(sys);

// //     // Fin du programme
// //     return 0;
// // }

#include "../includes/minishell.h"

// Affiche le type sous forme lisible au lieu du numéro
const char *ast_type_to_str(t_ast_type type)
{
    switch (type)
    {
        case AST_CMD: return "CMD";
        case AST_PIPE: return "PIPE";
        case AST_REDIR_IN: return "REDIR_IN";
        case AST_REDIR_OUT: return "REDIR_OUT";
        case AST_AND: return "AND";
        case AST_OR: return "OR";
        default: return "UNKNOWN";
    }
}
void	cleanup(t_sys *sys)
{
	if (sys)
	{
		if (sys->envp)
			gc_free_array((void **)sys->envp);
		// env_lst sera nettoyé par gc_destroy()
	}
	gc_destroy();
}

void	setup_signals(void)
{
	signal(SIGINT, SIG_IGN);  // Ignorer Ctrl+C pour l'instant
	signal(SIGQUIT, SIG_IGN); // Ignorer Ctrl+\ pour l'instant
}

void print_ast_verbose(t_ast *node, int level)
{
    if (!node)
        return;

    for (int i = 0; i < level; i++)
        printf("  ");
    printf("Node type: %s\n", ast_type_to_str(node->type));

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

    print_ast_verbose(node->left, level + 1);
    print_ast_verbose(node->right, level + 1);
}

// Vérifie que les liens left/right existent correctement sur un pipe (exemple)
int verify_pipe_structure(t_ast *node)
{
    if (!node || node->type != AST_PIPE)
        return 0;

    if (!node->left || !node->right)
    {
        fprintf(stderr, "Pipe node missing left or right child\n");
        return 0;
    }

    // Left et right doivent être des commandes ou d'autres pipes (récursif)
    if (node->left->type != AST_CMD && node->left->type != AST_PIPE)
    {
        fprintf(stderr, "Left child of pipe is not CMD or PIPE\n");
        return 0;
    }

    if (node->right->type != AST_CMD && node->right->type != AST_PIPE)
    {
        fprintf(stderr, "Right child of pipe is not CMD or PIPE\n");
        return 0;
    }

    return 1;
}

// Fonction générale de test d’une ligne de commande
int test_parse_line(t_sys *sys, const char *line, int expect_error)
{
    printf("\nTest parsing: %s\n", line);

    t_ast *ast = parse_line((char *)line, sys);

    if (expect_error)
    {
        if (ast)
        {
            printf("❌ Erreur attendue mais AST non NULL\n");
            free_ast(ast);
            return 0;
        }
        else
        {
            printf("✔️ Erreur détectée comme attendu\n");
            return 1;
        }
    }
    else
    {
        if (!ast)
        {
            printf("❌ Parsing a échoué\n");
            return 0;
        }

        print_ast_verbose(ast, 0);

        // Exemple de vérification structure pipe si on détecte un pipe en racine
        if (ast->type == AST_PIPE)
        {
            if (!verify_pipe_structure(ast))
            {
                printf("❌ Structure du pipe invalide\n");
                free_ast(ast);
                return 0;
            }
        }

        free_ast(ast);
        return 1;
    }
}

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

int main(int argc, char **argv, char **envp)
{

	(void)argc;
	(void)argv;
    t_sys *sys = init_sys(envp);
    if (!sys)
    {
        fprintf(stderr, "Failed to init sys\n");
        return 1;
    }

    setup_signals();

    int total = 0, passed = 0;

    // Tests valides
    passed += test_parse_line(sys, "ls -l", 0);
    total++;
    passed += test_parse_line(sys, "cat < input.txt", 0);
    total++;
    passed += test_parse_line(sys, "ls -l | grep \".c\"", 0);
    total++;
    passed += test_parse_line(sys, "echo 'hello world'", 0);
    total++;
    passed += test_parse_line(sys, "grep error file.txt > out.log", 0);
    total++;
    passed += test_parse_line(sys, "cmd1 && cmd2 || cmd3", 0);
    total++;
    passed += test_parse_line(sys, "cmd1 | cmd2 | cmd3", 0);
    total++;
    passed += test_parse_line(sys, "cmd < input > output", 0);
    total++;

    // Tests erreurs de syntaxe
    passed += test_parse_line(sys, "| ls", 1);
    total++;
    passed += test_parse_line(sys, "ls ||| grep", 1);
    total++;
    passed += test_parse_line(sys, "cat < ", 1);
    total++;
    passed += test_parse_line(sys, "echo 'unclosed quote", 1);
    total++;

    printf("\nTests réussis: %d / %d\n", passed, total);

    cleanup(sys);

    return (passed == total) ? 0 : 1;
}

