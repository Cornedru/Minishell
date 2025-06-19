#include "../libft/libft.h"
#include "../minishell.h"

int	is_command_position(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!current)
		return (1);
	while (current->next)
		current = current->next;
	if (current->type == TOKEN_PIPE)
		return (1);
	if (current->type == TOKEN_AND)
		return (1);
	if (current->type == TOKEN_OR)
		return (1);
	return (0);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	skip_whitespace(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

// int skip_par(char *input, int i)
// {
// 	while (input[i] && (input[i] == '(' || input[i] == ')'))
// 		i++;
// 	return (i);
// }

int	handle_quotes(char *input, int i, char quote)
{
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	else
		return (-1);
	return (i);
}

// int	check_unmatched_quotes(const char *line)
// {
// 	int		i;
// 	char	quote;

// 	i = 0;
// 	quote = 0;
// 	while (line[i])
// 	{
// 		if (quote == 0 && (line[i] == '\'' || line[i] == '"'))
// 			quote = line[i];
// 		else if (line[i] == quote)
// 			quote = 0;
// 		i++;
// 	}
// 	return (quote != 0);
// }
