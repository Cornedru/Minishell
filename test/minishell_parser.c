// #include "minishell.h"
// # include "libft/libft.h"

// volatile sig_atomic_t g_signal = 0;
// t_shell g_shell;



// #include "minishell.h"

// static int is_operator(char c)
// {
// 	return (c == '|' || c == '<' || c == '>');
// }

// static int skip_whitespace(char *input, int i)
// {
// 	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
// 		i++;
// 	return (i);
// }

// static int handle_quotes(char *input, int i, char quote)
// {
// 	i++;
// 	while (input[i] && input[i] != quote)
// 		i++;
// 	if (input[i] == quote)
// 		i++;
// 	return (i);
// }

// static char *extract_word(char *input, int start, int end)
// {
// 	char *word;
// 	int i, j;

// 	word = malloc(sizeof(char) * (end - start + 1));
// 	if (!word)
// 		return (NULL);
	
// 	i = start;
// 	j = 0;
// 	while (i < end)
// 	{
// 		if (input[i] == '\'' || input[i] == '"')
// 		{
// 			char quote = input[i];
// 			i++;
// 			while (i < end && input[i] != quote)
// 				word[j++] = input[i++];
// 			if (i < end)
// 				i++;
// 		}
// 		else
// 			word[j++] = input[i++];
// 	}
// 	word[j] = '\0';
// 	return (word);
// }

// static t_token_type get_operator_type(char *input, int i)
// {
// 	if (input[i] == '|')
// 		return (TOKEN_PIPE);
// 	else if (input[i] == '<')
// 	{
// 		if (input[i + 1] == '<')
// 			return (TOKEN_HEREDOC);
// 		return (TOKEN_REDIR_IN);
// 	}
// 	else if (input[i] == '>')
// 	{
// 		if (input[i + 1] == '>')
// 			return (TOKEN_REDIR_APPEND);
// 		return (TOKEN_REDIR_OUT);
// 	}
// 	return (TOKEN_WORD);
// }

// t_token *lexer(char *input)
// {
// 	t_token *tokens = NULL;
// 	int i = 0;
// 	int start;

// 	while (input[i])
// 	{
// 		i = skip_whitespace(input, i);
// 		if (!input[i])
// 			break;
		
// 		if (is_operator(input[i]))
// 		{
// 			t_token_type type = get_operator_type(input, i);
// 			char *value = NULL;
			
// 			if (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND)
// 			{
// 				value = ft_substr(input, i, 2);
// 				i += 2;
// 			}
// 			else
// 			{
// 				value = ft_substr(input, i, 1);
// 				i++;
// 			}
// 			add_token(&tokens, create_token(type, value));
// 		}
// 		else
// 		{
// 			start = i;
// 			while (input[i] && !is_operator(input[i]) && 
// 				   input[i] != ' ' && input[i] != '\t')
// 			{
// 				if (input[i] == '\'' || input[i] == '"')
// 					i = handle_quotes(input, i, input[i]);
// 				else
// 					i++;
// 			}
// 			char *word = extract_word(input, start, i);
// 			add_token(&tokens, create_token(TOKEN_WORD, word));
// 		}
// 	}
// 	return (tokens);
// }

// t_token *create_token(t_token_type type, char *value)
// {
// 	t_token *token = malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);
// 	token->type = type;
// 	token->value = value;
// 	token->next = NULL;
// 	return (token);
// }

// void add_token(t_token **tokens, t_token *new_token)
// {
// 	t_token *current;

// 	if (!*tokens)
// 	{
// 		*tokens = new_token;
// 		return;
// 	}
// 	current = *tokens;
// 	while (current->next)
// 		current = current->next;
// 	current->next = new_token;
// }

// void free_tokens(t_token *tokens)
// {
// 	t_token *current;
// 	t_token *next;

// 	current = tokens;
// 	while (current)
// 	{
// 		next = current->next;
// 		free(current->value);
// 		free(current);
// 		current = next;
// 	}
// }
// const char *get_token_type_name(t_token_type type)
// {
// 	switch (type)
// 	{
// 		case TOKEN_WORD: return "TOKEN_WORD";
// 		case TOKEN_PIPE: return "TOKEN_PIPE";
// 		case TOKEN_REDIR_IN: return "TOKEN_REDIR_IN";
// 		case TOKEN_REDIR_OUT: return "TOKEN_REDIR_OUT";
// 		case TOKEN_REDIR_APPEND: return "TOKEN_REDIR_APPEND";
// 		case TOKEN_HEREDOC: return "TOKEN_HEREDOC";
// 		default: return "UNKNOWN";
// 	}
// }

// void print_token_list(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		printf("Token: type=%d (%s), value=\"%s\"\n",
// 			tokens->type,
// 			get_token_type_name(tokens->type),
// 			tokens->value);
// 		tokens = tokens->next;
// 	}
// }


// #include "minishell.h"
// #include "libft/libft.h"
// #include <stdio.h>



// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s \"command line\"\n", argv[0]);
// 		return (1);
// 	}

// 	char *input = argv[1];
// 	t_token *tokens = lexer(input);

// 	if (!tokens)
// 	{
// 		printf("No tokens returned.\n");
// 		return (1);
// 	}

// 	print_token_list(tokens);
// 	free_tokens(tokens);
// 	return (0);
// }
