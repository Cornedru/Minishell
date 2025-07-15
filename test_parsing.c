// // /* ************************************************************************** */
// // /*                                                                            */
// // /*                                                        :::      ::::::::   */
// // /*   test_parsing.c                                     :+:      :+:    :+:   */
// // /*                                                    +:+ +:+         +:+     */
// // /*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
// // /*                                                +#+#+#+#+#+   +#+           */
// // /*   Created: 2025/07/03 00:00:00 by vous              #+#    #+#             */
// // /*   Updated: 2025/07/06 06:47:49 by ndehmej          ###   ########.fr       */
// // /*                                                                            */
// // /* ************************************************************************** */

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# include "../gc/includes/gc.h"
#include "../includes/minishell.h"

// volatile sig_atomic_t g_signal = 0;

// void	setup_signals(void)
// {
// 	signal(SIGINT, SIG_IGN);  // Ignorer Ctrl+C pour l'instant
// 	signal(SIGQUIT, SIG_IGN); // Ignorer Ctrl+\ pour l'instant
// }

// void print_ast(t_ast *node, int level)
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

// void	cleanup(t_sys *sys)
// {
// 	if (sys)
// 	{
// 		if (sys->envp)
// 		gc_free_array((void **)sys->envp);
// 	}
// 	gc_destroy();
// }

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

// int	process_line(char *line, t_sys *sys)
// {
// 	t_ast	*ast;
// 	int		status;

// 	ast = parse_line(line, sys);
// 	if (!ast)
// 	{
// 		sys->exit_status = 2;
// 		return (2);
// 	}
// 	if (getenv("DEBUG_AST"))
// 	{
// 		ft_putstr_fd("=== AST ===\n", 1);
// 		print_ast(ast, 0);
// 		ft_putstr_fd("===========\n", 1);
// 	}
// 	status = execute(ast, sys);
// 	sys->exit_status = status;
// 	free_ast(ast);
// 	return (status);
// }

// int	check_builtin_exit(char *line, t_sys *sys)
// {
// 	char	**args;
// 	int		i;

// 	args = gc_split(line, ' ');
// 	if (!args || !args[0])
// 		return (0);
// 	if (ft_strcmp(args[0], "exit") == 0)
// 	{
// 		ft_putstr_fd("exit\n", 1);
// 		sys->exit = 1;
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

// int	read_line(t_sys *sys)
// {
// 	char	*line;

// 	while (!sys->exit)
// 	{
// 		line = readline(PROMPT);
// 		if (!line)
// 		{
// 			ft_putstr_fd("exit\n", 1);
// 			break;
// 		}
// 		if (ft_strlen(line) == 0)
// 		{
// 			free(line);
// 			continue;
// 		}
// 		add_history(line);
// 		if (check_builtin_exit(line, sys))
// 		{
// 			free(line);
// 			break;
// 		}
// 		process_line(line, sys);
// 	}
// 		// free(line);
// 		return (0);
// }


// int	main(int argc, char **argv, char **envp)
// {
// 	t_sys	*sys;
// 	int		exit_status;

// 	if (argc > 1 && ft_strcmp(argv[1], "--test") == 0)
// 	{
// 		// run_parsing_tests();
// 		return (0);
// 	}
// 	if (argc > 1 && ft_strcmp(argv[1], "--debug-ast") == 0)
// 		setenv("DEBUG_AST", "1", 1);
// 	sys = init_sys(envp);
// 	if (!sys)
// 	{
// 		ft_putstr_fd("minishell: failed to initialize\n", 2);
// 		return (1);
// 	}
// 	setup_signals();
// 	if (isatty(STDIN_FILENO))
// 	{
// 		ft_putstr_fd("minishell v1.0\n", 1);
// 		ft_putstr_fd("Type 'exit' to quit\n", 1);
// 	}
// 	exit_status = read_line(sys);
// 	cleanup(sys);
// 	return (exit_status);
// }

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

// int main(int argc, char **argv, char **envp)
// {

// 	(void)argc;
// 	(void)argv;
//     t_sys *sys = init_sys(envp);
//     if (!sys)
//     {
//         fprintf(stderr, "Failed to init sys\n");
//         return 1;
//     }

//     setup_signals();

//     int total = 0, passed = 0;

//     // Tests valides
//     passed += test_parse_line(sys, "echo coucou > file1 file2 file3", 0);
//     total++;
//     passed += test_parse_line(sys, "cat < input.txt", 0);
//     total++;
//     passed += test_parse_line(sys, "ls -l | grep \".c\"", 0);
//     total++;
//     passed += test_parse_line(sys, "echo 'hello world'", 0);
//     total++;
//     passed += test_parse_line(sys, "grep error file.txt > out.log", 0);
//     total++;
//     passed += test_parse_line(sys, "cmd1 && cmd2 || cmd3", 0);
//     total++;
//     passed += test_parse_line(sys, "cmd1 | cmd2 | cmd3", 0);
//     total++;
//     passed += test_parse_line(sys, "cmd < input > output", 0);
//     total++;

//     // Tests erreurs de syntaxe
//     passed += test_parse_line(sys, "| ls", 1);
//     total++;
//     passed += test_parse_line(sys, "ls ||| grep", 1);
//     total++;
//     passed += test_parse_line(sys, "cat < ", 1);
//     total++;
//     passed += test_parse_line(sys, "echo 'unclosed quote", 1);
//     total++;

//     printf("\nTests réussis: %d / %d\n", passed, total);

//     cleanup(sys);

//     return (passed == total) ? 0 : 1;
// }

/* Exemple de fonction read_line intégrant le parsing */

// int	read_line(t_sys *sys)
// {
// 	char	*line;

// 	line = NULL;
// 	while (!sys->exit)
// 	{
// 		line = readline(PROMPT);
// 		if (!line)
// 		{
// 			ft_putstr_fd("exit\n", 1);
// 			return (0);
// 		}
// 		if (ft_strlen(line) > 0)
// 		{
// 			add_history(line);
// 			sys->ast = parse_line(line, sys);
// 			if (sys->ast)
// 			{
// 				sys->exit_status = execute(sys->ast, sys);
// 				free_ast(sys->ast);
// 				sys->ast = NULL;
// 			}
// 		}
// 		// gc_free(line);
// 	}
// 	return (0);
// }


int	read_line(t_sys *sys)
{
	char	*line;

	line = NULL;
	while (!sys->exit)
	{
		line = readline(PROMPT);
		if (!line)
			return (1);
		add_history(line);

		// Tokenize


		// Build AST
		//  { // ----------- MOCK AST ------------ //
		// if (!ft_strcmp(line, "ls -l"))
		// 	sys->ast = mock_ls_command();
		// if (!ft_strcmp(line, "cat < input.txt"))
		// 	sys->ast = mock_redir_in_command();
		// if (!ft_strcmp(line, "ls -l | grep \".c\""))
		// 	sys->ast = mock_pipe_command();
		// if (!ft_strcmp(line, "export A=1 B=2 A=new C 1INVALID"))
		// 	sys->ast = mock_export_command();
		// if (!ft_strcmp(line, "export"))
		// 	sys->ast = mock_export_no_args_command();
		// if (!ft_strcmp(line, "unset A C NONEXISTENT"))
		// 	sys->ast = mock_unset_command();
		// if (!ft_strcmp(line, "cd /tmp"))
		// 	sys->ast = mock_cd_command();
		// if (!ft_strcmp(line, "env"))
		// 	sys->ast = mock_env_command();
		// if (!ft_strcmp(line, "exit f42"))
		// 	sys->ast = mock_exit_command();
		// if (!ft_strcmp(line, "echo \"testing redir\" > output.txt"))
		// 	sys->ast = mock_redir_out_command();
		// if (!ft_strcmp(line, "wc -l << EOF"))
		// 	sys->ast = mock_heredoc_command();
		// }


		// Execute AST:
		if (sys->ast)
			sys->exit_status = execute(sys->ast, sys);
		gc_free(sys->ast);
	}
	return (0);
}

/* Fonction main complète */
// int	main(int argc, char **argv, char **envp)
// {
// 	t_sys	*sys;

// 	(void)argc;
// 	if (argc > 1 && !ft_strcmp(argv[1], "--test"))
// 	{
// 		//  run_parsing_tests();
// 		return (0);
// 	}
// 	if (init_shell(&sys, envp))
// 	{
// 		ft_putstr_fd("minishell: initialization failed\n", 2);
// 		return (1);
// 	}
// 	read_line(sys);
// 	gc_free_array((void **)sys->envp);
// 	gc_destroy();
// 	return (sys->exit_status);
// }



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

    printf("=== TESTS MINISHELL ===\n\n");

    // === COMMANDES SIMPLES ===
    printf("--- Commandes simples ---\n");
    passed += test_parse_line(sys, "ls", 0); total++;
    passed += test_parse_line(sys, "pwd", 0); total++;
    passed += test_parse_line(sys, "echo hello", 0); total++;
    passed += test_parse_line(sys, "echo hello world", 0); total++;
    passed += test_parse_line(sys, "/bin/ls", 0); total++;
    passed += test_parse_line(sys, "./minishell", 0); total++;

    // === QUOTES ===
    printf("\n--- Quotes ---\n");
    passed += test_parse_line(sys, "echo 'hello world'", 0); total++;
    passed += test_parse_line(sys, "echo \"hello world\"", 0); total++;
    passed += test_parse_line(sys, "echo 'hello \"world\"'", 0); total++;
    passed += test_parse_line(sys, "echo \"hello 'world'\"", 0); total++;
    passed += test_parse_line(sys, "echo \"hello $USER\"", 0); total++;
    passed += test_parse_line(sys, "echo 'hello $USER'", 0); total++;
    passed += test_parse_line(sys, "echo \"'quoted'\"", 0); total++;
    passed += test_parse_line(sys, "echo '\"double\"'", 0); total++;

    // === REDIRECTIONS SIMPLES ===
    printf("\n--- Redirections simples ---\n");
    passed += test_parse_line(sys, "echo hello > file", 0); total++;
    passed += test_parse_line(sys, "cat < file", 0); total++;
    passed += test_parse_line(sys, "echo world >> file", 0); total++;
    passed += test_parse_line(sys, "cat << EOF", 0); total++;
    passed += test_parse_line(sys, "> file echo hello", 0); total++;
    passed += test_parse_line(sys, "< input cat", 0); total++;
    passed += test_parse_line(sys, ">> file echo append", 0); total++;

    // === REDIRECTIONS MULTIPLES ===
    printf("\n--- Redirections multiples ---\n");
    passed += test_parse_line(sys, "cmd < input > output", 0); total++;
    passed += test_parse_line(sys, "cmd > out1 > out2", 0); total++;
    passed += test_parse_line(sys, "cmd < in1 < in2", 0); total++;
    passed += test_parse_line(sys, "> out < in cmd", 0); total++;
    passed += test_parse_line(sys, "cmd arg1 > file arg2", 0); total++;
    passed += test_parse_line(sys, "> file1 cmd arg > file2", 0); total++;

    // === PIPES ===
    printf("\n--- Pipes ---\n");
    passed += test_parse_line(sys, "ls | grep test", 0); total++;
    passed += test_parse_line(sys, "cat file | wc -l", 0); total++;
    passed += test_parse_line(sys, "echo hello | cat", 0); total++;
    passed += test_parse_line(sys, "ls -la | grep .c | wc -l", 0); total++;
    passed += test_parse_line(sys, "cmd1 | cmd2 | cmd3 | cmd4", 0); total++;

    // === OPÉRATEURS LOGIQUES ===
    printf("\n--- Opérateurs logiques ---\n");
    passed += test_parse_line(sys, "cmd1 && cmd2", 0); total++;
    passed += test_parse_line(sys, "cmd1 || cmd2", 0); total++;
    passed += test_parse_line(sys, "cmd1 && cmd2 || cmd3", 0); total++;
    passed += test_parse_line(sys, "cmd1 || cmd2 && cmd3", 0); total++;
    passed += test_parse_line(sys, "true && echo success", 0); total++;
    passed += test_parse_line(sys, "false || echo failed", 0); total++;

    // === COMBINAISONS COMPLEXES ===
    printf("\n--- Combinaisons complexes ---\n");
    passed += test_parse_line(sys, "echo test > file && cat < file", 0); total++;
    passed += test_parse_line(sys, "ls | grep .c > files.txt", 0); total++;
    passed += test_parse_line(sys, "cat < input | grep pattern > output", 0); total++;
    passed += test_parse_line(sys, "cmd1 && cmd2 | cmd3", 0); total++;
    passed += test_parse_line(sys, "cmd1 | cmd2 && cmd3", 0); total++;
    passed += test_parse_line(sys, "echo 'test' | cat > file || echo error", 0); total++;

    // === EXPANSION DE VARIABLES ===
    printf("\n--- Expansion de variables ---\n");
    passed += test_parse_line(sys, "echo $USER", 0); total++;
    passed += test_parse_line(sys, "echo $HOME/Documents", 0); total++;
    passed += test_parse_line(sys, "echo ${USER}", 0); total++;
    passed += test_parse_line(sys, "echo $?", 0); total++;
    passed += test_parse_line(sys, "echo $$", 0); total++;
    passed += test_parse_line(sys, "echo $NONEXISTENT", 0); total++;

    // === ERREURS DE SYNTAXE ===
    printf("\n--- Erreurs de syntaxe ---\n");
    passed += test_parse_line(sys, "|", 1); total++;
    passed += test_parse_line(sys, "| cmd", 1); total++;
    passed += test_parse_line(sys, "cmd |", 1); total++;
    passed += test_parse_line(sys, "cmd | | cmd", 1); total++;
    passed += test_parse_line(sys, "&&", 1); total++;
    passed += test_parse_line(sys, "||", 1); total++;
    passed += test_parse_line(sys, "cmd &&", 1); total++;
    passed += test_parse_line(sys, "|| cmd", 1); total++;
    passed += test_parse_line(sys, ">", 1); total++;
    passed += test_parse_line(sys, "<", 1); total++;
    passed += test_parse_line(sys, "cmd >", 1); total++;
    passed += test_parse_line(sys, "< cmd", 1); total++;
    passed += test_parse_line(sys, "cmd > >", 1); total++;
    passed += test_parse_line(sys, "cmd < <", 1); total++;

    // === QUOTES NON FERMÉES ===
    printf("\n--- Quotes non fermées ---\n");
    passed += test_parse_line(sys, "echo 'hello", 1); total++;
    passed += test_parse_line(sys, "echo \"world", 1); total++;
    passed += test_parse_line(sys, "echo 'hello \"world'\"", 1); total++;
    passed += test_parse_line(sys, "echo \"hello 'world\"'", 1); total++;

    // === CAS LIMITES ===
    printf("\n--- Cas limites ---\n");
    passed += test_parse_line(sys, "", 1); total++;
    passed += test_parse_line(sys, "   ", 1); total++;
    passed += test_parse_line(sys, "\t\t", 1); total++;
    passed += test_parse_line(sys, "cmd arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10", 0); total++;
    passed += test_parse_line(sys, "echo \"\"", 0); total++;
    passed += test_parse_line(sys, "echo ''", 0); total++;
    passed += test_parse_line(sys, "echo \"\" ''", 0); total++;

    // === CARACTÈRES SPÉCIAUX ===
    printf("\n--- Caractères spéciaux ---\n");
    passed += test_parse_line(sys, "echo \\$USER", 0); total++;
    passed += test_parse_line(sys, "echo 'a;b'", 0); total++;
    passed += test_parse_line(sys, "echo \"a;b\"", 0); total++;
    passed += test_parse_line(sys, "echo test\\ with\\ spaces", 0); total++;
    
    // === REDIRECTIONS AVEC ARGUMENTS ===
    printf("\n--- Redirections avec arguments ---\n");
    passed += test_parse_line(sys, "echo one > file two three", 0); total++;
    passed += test_parse_line(sys, "> file echo one two three", 0); total++;
    passed += test_parse_line(sys, "echo one two > file three four", 0); total++;
    passed += test_parse_line(sys, "cat file1 file2 > output", 0); total++;
    passed += test_parse_line(sys, "< input grep pattern file", 0); total++;

    // === PIPES AVEC REDIRECTIONS ===
    printf("\n--- Pipes avec redirections ---\n");
    passed += test_parse_line(sys, "cat < file | grep test", 0); total++;
    passed += test_parse_line(sys, "ls | grep .c > output", 0); total++;
    passed += test_parse_line(sys, "< input cmd1 | cmd2 > output", 0); total++;
    passed += test_parse_line(sys, "cmd1 > tmp | cmd2", 0); total++;

    // === OPÉRATEURS MIXTES ===
    printf("\n--- Opérateurs mixtes ---\n");
    passed += test_parse_line(sys, "cmd1 && cmd2 | cmd3 || cmd4", 0); total++;
    passed += test_parse_line(sys, "(cmd1 || cmd2) && cmd3", 0); total++;
    passed += test_parse_line(sys, "test -f file && echo exists || echo not found", 0); total++;

    printf("\n=== RÉSULTATS FINAUX ===\n");
    printf("Tests réussis: %d / %d\n", passed, total);
    printf("Taux de réussite: %.2f%%\n", (float)passed / total * 100);

    cleanup(sys);
    return (passed == total) ? 0 : 1;
}