/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:34:42 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/08 20:03:13 by ndehmej          ###   ########.fr       */
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

// int	read_line(t_sys *sys)
// {
// 	char	*line;

// 	line = NULL;
// 	while (!(sys->exit))
// 	{
// 		line = readline("MiniShell> ");
// 		if (!line)
// 			return (0);
// 		if (ft_strlen(line) > 0)
// 		{
// 			add_history(line);

// 			// Tokenize

// 			// Build AST
// 			// ----------- MOCK AST ------------
// 			// sys->ast = mock_ls_command();
// 			// sys->ast = mock_redir_command();
// 			sys->ast = mock_pipe_command();
// 			// ---------------------------------

// 			// Execute AST:
// 			if (sys->ast)
// 				sys->exit_status = execute(sys->ast, sys);
// 			gc_free(sys->ast);
// 		}
// 		else
// 			printf("(empty line)\n");
// 	}
// 	return (1);
// }

// void cleanup(t_sys *sys) {
//     // Libérer environnement
//     for (char **e = sys->env; *e; e++) 
//         free(*e);
//     free(sys->env);
    
//     // Libérer tableau environnement
//     free(sys->env_array);
// }

// void	run_parsing_tests(void);

// Dans main(), ajouter une option de test
// int main(int argc, char const **argv, char **envp)
// {
// 	t_sys	*sys;

// 	// Mode test si --test est passé en argument
// 	if (argc > 1 && !ft_strcmp(argv[1], "--test"))
// 	{
// 		run_parsing_tests();
// 		return (0);
// 	}

// 	// Code normal...
// 	sys = init_sys(envp);
// 	read_line(sys);
// 	gc_free_array((void **)sys->envp);
// 	gc_destroy();
// 	// atexit(cleanup); 
// 	return (0);
// }

// int main(int argc, char const **argv, char **envp)
// {
// 	t_sys	*sys;

// 	(void)argc;
// 	(void)argv;

// 	sys = init_sys(envp);

// 	read_line(sys);

// 	gc_free_array((void **)sys->envp);
// 	gc_destroy();
// 	return (0);
// }



