#include "../libft/libft.h"
#include "../minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	if (type == TOKEN_ARG)
		return ("TOKEN_ARG");
	else if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	else if (type == TOKEN_REDIR_IN)
		return ("TOKEN_REDIR_IN");
	else if (type == TOKEN_REDIR_OUT)
		return ("TOKEN_REDIR_OUT");
	else if (type == TOKEN_REDIR_APPEND)
		return ("TOKEN_REDIR_APPEND");
	else if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	else if (type == TOKEN_CMD)
		return ("TOKEN_CMD");
	else if (type == TOKEN_AND)
		return ("TOKEN_AND");
	else if (type == TOKEN_OR)
		return ("TOKEN_OR");
	else if (type == TOKEN_FILE)
		return ("TOKEN_FILE");
	else if (type == TOKEN_ERROR)
		return ("TOKEN_ERROR");
	else
		return ("UNKONW");
}

void	print_token_list(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: type=%d (%s), value=\"%s\"\n", tokens->type,
			get_token_type_name(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}

t_token_type	get_operator_type(char *input, int i)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			return (TOKEN_OR);
		return (TOKEN_PIPE);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (TOKEN_REDIR_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	else if (input[i] == '&')
	{
		if (input[i + 1] == '&')
			return (TOKEN_AND);
		return (TOKEN_ERROR);
	}
	return (TOKEN_ERROR);
}