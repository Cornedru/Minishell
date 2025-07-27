#include "includes/minishell.h"
#include <signal.h>

volatile sig_atomic_t	g_signal = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = SIG_INTERRUPT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static int	process_line(char *line, t_sys *sys)
{
	t_ast	*ast;
	int		status;

	if (!line || !*line)
		return (0);
	ast = parse_line(line, sys);
	if (!ast)
		return (1);
	status = execute(ast, sys);
	free_ast(ast);
	sys->exit_status = status;
	return (status);
}

// static int	shell_loop(t_sys *sys)
// {
// 	char	*line;
// 	int		stdin_copy;

// 	stdin_copy = dup(STDIN_FILENO);
// 	while (!sys->exit)
// 	{
// 		if (g_signal == SIG_INTERRUPT)
// 		{
// 			sys->exit_status = 130;
// 			g_signal = SIG_NONE;
// 		}
// 		line = readline(PROMPT);
// 		if (!line)
// 		{
// 			ft_putstr_fd("exit\n", 1);
// 			break ;
// 		}
// 		if (*line)
// 			add_history(line);
// 		process_line(line, sys);
// 		gc_free(line);
// 		dup2(stdin_copy, STDIN_FILENO);
// 	}
// 	close(stdin_copy);
// 	return (sys->exit_status);
// }

void gc_clear_all(t_gc *gc)
{
    t_gc_node *node;
    t_gc_node *tmp;

	node = NULL;
	if (!node)
    	return;
    node = gc->permanent;
    while (node)
    {
        free(node->ptr);
        tmp = node;
        node = node->next;
        free(tmp);
    }
    gc->permanent = NULL;
    node = gc->temporary;
    while (node)
    {
        free(node->ptr);
        tmp = node;
        node = node->next;
        free(tmp);
    }
    gc->temporary = NULL;
}

static int	shell_loop(t_sys *sys)
{
	char	*line;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	while (!sys->exit)
	{
		if (g_signal == SIG_INTERRUPT)
		{
			sys->exit_status = 130;
			g_signal = SIG_NONE;
		}
		line = readline(PROMPT);
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*line)
			add_history(line);
		process_line(line, sys);
		gc_free(line);
		dup2(stdin_copy, STDIN_FILENO);

		// ✅ Libère tout ce qui a été malloc dans cette boucle
		gc_clear_all(sys->gc);
	}
	close(stdin_copy);
	return (sys->exit_status);
}


// int	main(int argc, char **argv, char **envp)
// {
// 	t_sys	*sys;
// 	int		exit_status;

// 	(void)argc;
// 	(void)argv;
// 	setup_signals();
// 	if (init_shell(&sys, envp))
// 		return (1);
// 	exit_status = shell_loop(sys);
// 	gc_destroy();
// 	rl_clear_history();
// 	return (exit_status);
// }




// int	main(int argc, char **argv, char **envp)
// {
// 	t_sys	*sys;
// 	int		exit_status;

// 	(void)argc;
// 	(void)argv;
// 	setup_signals();
// 	if (init_shell(&sys, envp))
// 		return (1);
// 	exit_status = shell_loop(sys);

// 	// Affiche les fuites mémoire avant de détruire le GC
// 	gc_print_leaks();    // 🔍 DEBUG
	
// 	// gc_clear_all(sys->gc);
// 	gc_destroy();
// 	rl_clear_history();
// 	return (exit_status);
// }

int main(int argc, char **argv, char **envp)
{
    t_sys *sys;
    int exit_status;

    (void)argc;
    (void)argv;
    setup_signals();
    if (init_shell(&sys, envp))
        return (1);
    exit_status = shell_loop(sys);

    // Affiche les fuites pour debug
    gc_clear_all(sys->gc);      
    gc_destroy();               
    rl_clear_history();
    return (exit_status);
}

you must also verify the abscence of memory leak. any memory allocated on the heap must be properly freed before the end of execution.
you are allowed to use any of the different tools available ont the cumputer, such as leaks, valgrind, or e_fence.