#include "../minishell.h"
#include "../libft/libft.h"

char 							*builtin_commands[] = {
	"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
};

int	is_builtin_command(char *word)
{
	int i = 0;
	
	if (!word)
		return (0);
	while (builtin_commands[i])
	{
		if (ft_strcmp(word, builtin_commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

// int is_file(t_token *tokens)
// {
// 	t_token	*current;

// 	current = tokens;
// 	if (!current)
// 		return (1);
// 	while (current)
// 	{
// 		if (!ft_strncmp(ft_strlen(current), ".", 1))
// 			return (1);
// 		return (0);
// 	}
// 	return (0);
// }