#include "minishell.h"

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == '('
		|| c == ')');
}

static int	skip_whitespace(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

static int	handle_quotes(char *input, int i, char quote)
{
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	return (i);
}

static char	*extract_word(char *input, int start, int end)
{
	char	*word;
	char	quote;

	int i, j;
	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			while (i < end && input[i] != quote)
				word[j++] = input[i++];
			if (i < end)
				i++;
		}
		else
			word[j++] = input[i++];
	}
	word[j] = '\0';
	return (word);
}

static t_token_type	get_operator_type(char *input, int i)
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
	else if (input[i] == '&' && input[i + 1] == '&')
		return (TOKEN_AND);
	else if (input[i] == '(')
		return (TOKEN_LPAREN);
	else if (input[i] == ')')
		return (TOKEN_RPAREN);
	return (TOKEN_WORD);
}

t_token	*lexer(char *input)
{
	t_token *tokens = NULL;
	int i = 0;
	int start;

	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;

		if (is_operator(input[i]))
		{
			t_token_type type = get_operator_type(input, i);
			char *value = NULL;

			if (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND
				|| type == TOKEN_AND || type == TOKEN_OR)
			{
				value = ft_substr(input, i, 2);
				i += 2;
			}
			else
			{
				value = ft_substr(input, i, 1);
				i++;
			}
			add_token(&tokens, create_token(type, value));
		}
		else
		{
			start = i;
			while (input[i] && !is_operator(input[i]) && input[i] != ' '
				&& input[i] != '\t')
			{
				if (input[i] == '\'' || input[i] == '"')
					i = handle_quotes(input, i, input[i]);
				else
					i++;
			}
			char *word = extract_word(input, start, i);
			add_token(&tokens, create_token(TOKEN_WORD, word));
		}
	}
	return (tokens);
}