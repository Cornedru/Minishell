#include "../minishell.h"
#include "../libft/libft.h"


volatile sig_atomic_t	g_signal = 0;
t_shell					g_shell = {0};