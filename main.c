#include "minishell.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
// int	main(void)
// {
// 	char	*line;
// 	size_t	len;
// 	ssize_t	read;
// 	t_token	*tokens;

// 	line = NULL;
// 	len = 0;
// 	printf("MiniShell Lexer Test\n");
// 	while (1)
// 	{
// 		printf("> ");
// 		read = getline(&line, &len, stdin);
// 		if (read == -1)
// 			break ;
// 		if (read > 0 && line[read - 1] == '\n')
// 			line[read - 1] = '\0';
// 		if (strcmp(line, "exit") == 0)
// 			break ;
// 		tokens = lexer(line);
// 		if (!tokens)
// 		{
// 			fprintf(stderr, "Lexer error\n");
// 			continue ;
// 		}
// 		print_token_list(tokens);
// 		free_tokens(tokens);
// 	}
// 	free(line);
// 	return (0);
// }

int	main(void)
{
    char	*input;
    t_token	*tokens;

    while (1)
    {
        input = read_complete_line();
        if (!input)
            break ;
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        add_history(input);
        tokens = lexer(input);
        free(input);
        if (!tokens)
        {
            break;
        }
        
        t_token *error_token = NULL;
        t_token *current = tokens;
        while (current)
        {
            if (current->type == TOKEN_ERROR)
            {
                error_token = current;
                break;
            }
            current = current->next;
        }
        // if (error_token)
        // {
        //     printf("minishell: %s\n", error_token->value);
        //     free_tokens(tokens);
        //     continue;
        // }
        print_token_list(tokens);
        free_tokens(tokens);
    }
    return (0);
}
