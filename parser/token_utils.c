#include "../libft/libft.h"
#include "../minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

t_token_type	determine_word_type(char *word, t_token *tokens)
{
	if (is_command_position(tokens))
	{
		if (is_builtin_command(word))
			return (TOKEN_CMD);
		return (TOKEN_CMD);
		// if (is_file(word))
		// 	return (TOKEN_FILE);
	}
	return (TOKEN_ARG);
}

int	contains_error_token(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_ERROR)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
