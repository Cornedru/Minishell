/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:00:00 by vous              #+#    #+#             */
/*   Updated: 2025/07/03 07:28:56 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// void	print_ast(t_ast *node, int level)
// {
// 	if (!node)
// 		return;
// 	for (int i = 0; i < level; i++)
// 		printf("  ");
// 	printf("Node type: %d\n", node->type);

// 	if (node->args)
// 	{
// 		for (int i = 0; node->args[i]; i++)
// 		{
// 			for (int j = 0; j < level + 1; j++)
// 				printf("  ");
// 			printf("Arg: %s\n", node->args[i]);
// 		}
// 	}

// 	if (node->filename)
// 	{
// 		for (int i = 0; i < level + 1; i++)
// 			printf("  ");
// 		printf("File: %s\n", node->filename);
// 	}

// 	print_ast(node->left, level + 1);
// 	print_ast(node->right, level + 1);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_token *tokens;
// 	t_ast	*ast;
// 	t_sys	*sys;

// 	(void)argc;
// 	(void)argv;

// 	sys = init_sys(envp);
// 	while (1)
// 	{
// 		input = readline("TEST_PARSE$ ");
// 		if (!input)
// 			break;

// 		if (check_quotes(input))
// 		{
// 			printf("Unmatched quotes!\n");
// 			continue;
// 		}

// 		tokens = lexer(input);
// 		expand_tokens(tokens, sys);
// 		ast = parse(&tokens);

// 		printf("=== AST Structure ===\n");
// 		print_ast(ast, 0);
// 		printf("=====================\n");

// 		free_tokens(tokens);
// 		free_ast(ast);
// 		free(input);
// 	}
// 	return (0);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "includes/minishell.h"

// void print_ast(t_ast *ast);

// void test_input(char *input)
// {
//     printf("=== TEST INPUT ===\n");
//     printf("Input: %s\n", input);
//     t_token *tokens = lexer(input);
//     t_ast   *ast = parse(&tokens);   // <- ici

//     printf("=== AST ===\n");
//     print_ast(ast);
//     printf("=====================\n");

//     free_tokens(tokens);
//     free_ast(ast);
// }

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;

//     t_sys *sys = init_sys(envp);

//     // Cas simples
//     test_input("ls -la");
//     test_input("echo Hello World");
//     test_input("pwd");

//     // Redirections
//     test_input("cat < input.txt");
//     test_input("echo 'hello' > file.txt");
//     test_input("grep test < input.txt > output.txt");

//     // Pipes
//     test_input("ls -la | grep .c");
//     test_input("cat file | sort | uniq");

//     // Variables (en supposant expanseur actif)
//     test_input("echo $HOME");
//     test_input("echo \"$USER is logged in\"");

//     // Quotes
//     test_input("echo \"hello world\"");
//     test_input("echo 'single quoted $VAR'");
//     test_input("echo \"double quoted $VAR\"");

//     // Mixed
//     test_input("echo \"$USER\" | grep root > out.txt");
//     test_input("cat < infile | grep \"pattern\" | sort > outfile");

//     // Espaces, tabs, etc.
//     test_input("    ls      -l     ");
//     test_input("\techo\thello");

//     // Syntaxe invalide (facultatif)
//     test_input("cat <");
//     test_input("echo | | ls");

//     (void)sys; // si tu ne l'utilises pas pour éviter warning

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include "includes/minishell.h"

// const char *node_type_name(int type)
// {
//     if (type == 0) return "CMD";
//     if (type == 1) return "PIPE";
//     if (type == 6) return "AND";
//     // ajoute tous tes types ici...
//     return "UNKNOWN";
// }

// // Ton print_ast avec niveau indenté


// // Fonction de test simple (pour appel dans suite)
// void test_input(char *input, t_sys *sys)
// {
//     printf("=== TEST INPUT ===\n");
//     printf("Input: %s\n", input);
//     t_token *tokens = lexer(input);
//     expand_tokens(tokens, sys);
//     t_ast *ast = parse(&tokens);

//     printf("=== AST Structure ===\n");
//     print_ast(ast, 0);
//     printf("=====================\n");

//     free_tokens(tokens);
//     free_ast(ast);
// }

// // Suite de tests complexes
// void test_complex_suite(t_sys *sys)
// {
//     test_input("ls -la /tmp", sys);
//     test_input("echo Hello World", sys);
//     test_input("pwd", sys);

//     test_input("cat < input.txt", sys);
//     test_input("echo 'hello' > file.txt", sys);
//     test_input("grep test < input.txt > output.txt", sys);

//     test_input("ls -la | grep .c", sys);
//     test_input("cat file | sort | uniq", sys);

//     test_input("echo $HOME", sys);
//     test_input("echo \"$USER is logged in\"", sys);
//     test_input("echo '$USER will not expand'", sys);
//     test_input("echo \"Mixing $SHELL and 'quotes'\"", sys);

//     test_input("cat < infile | grep pattern > outfile", sys);
//     test_input("echo \"multi\nline\" | grep line", sys);

//     test_input("cat file1 | grep pattern > result.txt | sort", sys);

//     test_input("echo \"She said \\\"Hello\\\"\"", sys);
//     test_input("echo 'It\\'s a test'", sys);

//     test_input("echo $UNDEFINED_VAR", sys);
//     test_input("echo ${USER:-default}", sys);

//     test_input("    ls\t-l  \t  /tmp  ", sys);
//     test_input("echo \n Hello \n World", sys);

//     test_input("cat <", sys);
//     test_input("echo | | ls", sys);
//     test_input("grep 'unclosed_quote", sys);
//     test_input("echo \"unclosed double quote", sys);

//     test_input("echo append >> file.txt", sys);
//     test_input("cat file.txt >> output.txt", sys);

//     test_input("cd /tmp && ls | grep file", sys);

//     test_input("find / -type f | grep minishell | sort | uniq > result.log", sys);

//     test_input("echo \"A 'nested' quote\"", sys);
//     test_input("echo 'A \"nested\" quote'", sys);

//     test_input("echo      multiple      spaces", sys);
//     test_input("echo\tmixed\tspaces\tand\ttabs", sys);
// }

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;

//     t_sys *sys = init_sys(envp);

//     // Lancer la suite de tests complexes au démarrage
//     printf("==== Lancement de la suite de tests complexes ====\n");
//     test_complex_suite(sys);
//     printf("==== Fin des tests ====\n\n");

//     // Boucle REPL interactive
//     while (1)
//     {
//         char *input = readline("TEST_PARSE$ ");
//         if (!input)
//             break;

//         if (check_quotes(input))
//         {
//             printf("Unmatched quotes!\n");
//             free(input);
//             continue;
//         }

//         t_token *tokens = lexer(input);
//         expand_tokens(tokens, sys);
//         t_ast *ast = parse(&tokens);

//         printf("=== AST Structure ===\n");
//         print_ast(ast, 0);
//         printf("=====================\n");

//         free_tokens(tokens);
//         free_ast(ast);
//         free(input);
//     }

//     return 0;
// }

// #include "../includes/minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/wait.h>

// volatile sig_atomic_t g_signal = 0;

// t_sys	*init_sys(char **envp)
// {
// 	t_sys	*sys;

// 	sys = (t_sys *)gc_malloc(sizeof(t_sys));
// 	sys->env_lst = pull_env(envp);
// 	sys->envp = dup_array(envp);
// 	sys->token = NULL;
// 	sys->ast = NULL;
// 	sys->exit = 0;
// 	return (sys);
// }


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

// int check_bash_syntax(const char *cmd)
// {
//     int status;
//     pid_t pid = fork();
//     if (pid == 0) {
//         // Fils : exécute bash -n
//         execlp("bash", "bash", "-n", "-c", cmd, NULL);
//         _exit(127); // en cas d’erreur execlp
//     } else if (pid > 0) {
//         waitpid(pid, &status, 0);
//         if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
//             return 1; // syntax OK
//         else
//             return 0; // syntax error
//     }
//     return 0; // erreur fork
// }

// void test_and_compare(char *input, t_sys *sys)
// {
//     printf("=== TEST INPUT ===\nInput: %s\n", input);
//     if (!check_bash_syntax(input))
//     {
//         printf("Bash détecte une erreur de syntaxe.\n");
//     }
//     else
//     {
//         t_token *tokens = lexer(input);
//         if (!tokens)
//         {
//             printf("Lexer a échoué.\n");
//             return;
//         }
//         expand_tokens(tokens, sys);
//         t_ast *ast = parse(&tokens);
//         if (!ast)
//         {
//             printf("Parser a échoué.\n");
//         }
//         else
//         {
//             printf("AST généré:\n");
//             print_ast(ast, 0);
//             free_ast(ast);
//         }
//         free_tokens(tokens);
//     }
//     printf("=====================\n\n");
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_sys *sys = init_sys(envp);
// 	(void)argc;
// 	(void)argv;

//     // Liste de tests à faire
//     char *tests[] = {
//         "ls -la /tmp",
//         "echo Hello World",
//         "cat < input.txt",
//         "echo 'hello' > file.txt",
//         "grep test < input.txt > output.txt",
//         "ls -la | grep .c",
//         "cat file | sort | uniq",
//         "echo $HOME",
//         "echo 'unmatched quote",
//         "echo | | ls",
//         NULL
//     };

//     for (int i = 0; tests[i]; i++)
//         test_and_compare(tests[i], sys);

//     return 0;
// }


// #include "../includes/minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// volatile sig_atomic_t g_signal = 0;

// void free_sys(t_sys *sys)
// {
//     if (!sys)
//         return;
//     free_env_list(sys->env_lst);  // ta fonction d'environnements
//     free_array(sys->envp);        // ta fonction pour tableau de strings
//     free_tokens(sys->token);
//     free_ast(sys->ast);
//     free(sys);
// }

// t_sys *init_sys(char **envp)
// {
//     t_sys *sys;

//     sys = (t_sys *)gc_malloc(sizeof(t_sys));
//     sys->env_lst = pull_env(envp);
//     sys->envp = dup_array(envp);
//     sys->token = NULL;
//     sys->ast = NULL;
//     sys->exit = 0;
//     return (sys);
// }

// void print_ast_line(t_ast *node)
// {
//     if (!node)
//         return;
//     printf("Type:%d Args:", node->type);
//     if (node->args)
//     {
//         for (int i = 0; node->args[i]; i++)
//             printf("%s,", node->args[i]);
//     }
//     printf("\n");
//     if (node->left)
//         print_ast_line(node->left);
//     if (node->right)
//         print_ast_line(node->right);
// }

// int check_bash_syntax(const char *cmd)
// {
//     int status;
//     pid_t pid = fork();

//     if (pid == 0)
//     {
//         // Fils : exécute bash -n (check syntax)
//         execlp("bash", "bash", "-n", "-c", cmd, NULL);
//         _exit(127); // erreur execlp
//     }
//     else if (pid > 0)
//     {
//         waitpid(pid, &status, 0);
//         if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
//             return 1; // syntax OK
//         else
//             return 0; // syntax error
//     }
//     return 0; // fork error
// }

// void test_and_compare(char *input, t_sys *sys)
// {
//     printf("=== TEST INPUT ===\nInput: %s\n", input);
//     int bash_ok = check_bash_syntax(input);

//     t_token *tokens = NULL;
//     t_ast *ast = NULL;

//     if (!bash_ok)
//     {
//         printf("Bash détecte une erreur de syntaxe.\n");
//     }

//     tokens = lexer(input);
//     if (!tokens)
//     {
//         printf("Lexer a échoué.\n");
//     }
//     else
//     {
//         expand_tokens(tokens, sys);
//         ast = parse(&tokens);
//     }

//     if (bash_ok && ast)
//     {
//         printf("AST généré:\n");
//         print_ast_line(ast);
//         printf("Test OK: syntaxe valide et AST généré.\n");
//     }
//     else if (!bash_ok && !ast)
//     {
//         printf("Test OK: erreur de syntaxe détectée par bash et minishell.\n");
//     }
//     else
//     {
//         printf("Discrepance détectée !\n");
//         if (!bash_ok)
//             printf("Bash détecte une erreur, mais minishell a généré un AST.\n");
//         else
//             printf("Bash valide la syntaxe, mais minishell n'a pas généré d'AST.\n");
//     }

//     if (ast)
//         free_ast(ast);
//     if (tokens)
//         free_tokens(tokens);

//     printf("=====================\n\n");
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_sys *sys = init_sys(envp);
//     (void)argc;
//     (void)argv;

//     char *tests[] = {
//         "ls -la /tmp",
//         "echo Hello World",
//         "cat < input.txt",
//         "echo 'hello' > file.txt",
//         "grep test < input.txt > output.txt",
//         "ls -la | grep .c",
//         "cat file | sort | uniq",
//         "echo $HOME",
//         "echo 'unmatched quote",
//         "echo | | ls",
//         NULL};

//     for (int i = 0; tests[i]; i++)
//         test_and_compare(tests[i], sys);

//     // À la fin, libérer sys et son contenu si nécessaire
// 	free_sys(sys);

//     return 0;
// }


#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t g_signal = 0;

t_sys *init_sys(char **envp)
{
    t_sys *sys;

    sys = (t_sys *)gc_malloc(sizeof(t_sys));
    sys->env_lst = pull_env(envp);
    sys->envp = dup_array(envp);
    sys->token = NULL;
    sys->ast = NULL;
    sys->exit = 0;
    return (sys);
}

void print_ast_line(t_ast *node)
{
    if (!node)
        return;
    printf("Type:%d Args:", node->type);
    if (node->args)
    {
        for (int i = 0; node->args[i]; i++)
            printf("%s,", node->args[i]);
    }
    printf("\n");
    if (node->left)
        print_ast_line(node->left);
    if (node->right)
        print_ast_line(node->right);
}

int check_bash_syntax(const char *cmd)
{
    int status;
    pid_t pid = fork();

    if (pid == 0)
    {
        // Fils : exécute bash -n (check syntax)
        execlp("bash", "bash", "-n", "-c", cmd, NULL);
        _exit(127); // erreur execlp
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            return 1; // syntax OK
        else
            return 0; // syntax error detected by bash
    }
    return 0; // fork error
}

void test_and_compare(char *input, t_sys *sys)
{
    printf("=== TEST INPUT ===\nInput: %s\n", input);
    int bash_detected_syntax_ok = check_bash_syntax(input);
    int bash_detected_syntax_error = !bash_detected_syntax_ok;

    t_token *tokens = NULL;
    t_ast *ast = NULL;

    tokens = lexer(input);
    if (!tokens)
    {
        printf("Lexer a échoué.\n");
    }
    else
    {
        expand_tokens(tokens, sys);
        ast = parse(&tokens);
    }

    if (!ast)
    {
        if (bash_detected_syntax_error)
            printf("Test OK: erreur syntaxe détectée par bash et minishell.\n");
        else
            printf("Parser a échoué mais bash n’a pas détecté d’erreur.\n");
    }
    else
    {
        if (!bash_detected_syntax_error)
        {
            printf("AST généré:\n");
            print_ast_line(ast);
            printf("Test OK: syntaxe valide et AST généré.\n");
        }
        else
        {
            printf("Discrepance détectée ! Bash détecte une erreur, mais minishell a généré un AST.\n");
            printf("AST généré (potentiellement incorrect):\n");
            print_ast_line(ast);
        }
        free_ast(ast);
    }

    if (tokens)
        free_tokens(tokens);

    printf("=====================\n\n");
}

int main(int argc, char **argv, char **envp)
{
    t_sys *sys = init_sys(envp);
    (void)argc;
    (void)argv;

    char *tests[] = {
        "ls -la /tmp",
        "echo Hello World",
        "cat < input.txt",
        "echo 'hello' > file.txt",
        "grep test < input.txt > output.txt",
        "ls -la | grep .c",
        "cat file | sort | uniq",
        "echo $HOME",
        "echo 'unmatched quote",
        "echo | | ls",
        NULL};

    for (int i = 0; tests[i]; i++)
        test_and_compare(tests[i], sys);

    // Libérations éventuelles de sys ici si nécessaire

    return 0;
}


