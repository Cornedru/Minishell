#include "../libft/libft.h"
#include "../minishell.h"

char	*extract_word(char *input, int start, int end)
{
	char	*word;
	char	quote;
	int		i;
	int		j;

	word = malloc(sizeof(char) * (end - start + 1));
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

t_token	*lexer(char *input)
{
	t_token			*tokens;
	int				i;
	int				start;
	t_token_type	type;
	char			*value;
	char			*word;
	int				new_i;
	
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		// i = skip_par(input, i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
		{
			type = get_operator_type(input, i);
			value = NULL;
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
				{
					new_i = handle_quotes(input, i, input[i]);
					if (new_i == -1)
					{
						word = ft_substr(input, start, ft_strlen(input));
						if (!word)
						{
							free_tokens(tokens);
							return (NULL);
						}
						add_token(&tokens, create_token(TOKEN_ERROR, word));
						return (tokens);
					}
					i = new_i;
				}
				else
					i++;
			}
			word = extract_word(input, start, i);
			if (!word)
			{
				free_tokens(tokens);
				return (NULL);
			}
			type = determine_word_type(word, tokens);
			add_token(&tokens, create_token(type, word));
		}
	}
	return (tokens);
}
