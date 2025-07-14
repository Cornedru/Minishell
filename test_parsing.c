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

int	read_line(t_sys *sys)
{
	char	*line;

	line = NULL;
	while (!sys->exit)
	{
		line = readline(PROMPT);
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			return (0);
		}
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			sys->ast = parse_line(line, sys);
			if (sys->ast)
			{
				sys->exit_status = execute(sys->ast, sys);
				free_ast(sys->ast);
				sys->ast = NULL;
			}
		}
		free(line);
	}
	return (0);
}

/* Fonction main complète */
int	main(int argc, char **argv, char **envp)
{
	t_sys	*sys;

	(void)argc;
	if (argc > 1 && !ft_strcmp(argv[1], "--test"))
	{
		// run_parsing_tests();
		return (0);
	}
	if (init_shell(&sys, envp))
	{
		ft_putstr_fd("minishell: initialization failed\n", 2);
		return (1);
	}
	read_line(sys);
	gc_free_array((void **)sys->envp);
	gc_destroy();
	return (sys->exit_status);
}