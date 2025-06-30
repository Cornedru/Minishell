#include "minishell.h"

char	**gather_all_words(t_token **tokens)
{
	t_token	*start;
	t_token	*tmp;
	int		count;
	char	**argv;
	int		i;
	char	*clean_str;

	start = *tokens;
	count = 0;
	tmp = start;
	while (tmp && tmp->type != TOKEN_PIPE && tmp->type != TOKEN_AND
		&& tmp->type != TOKEN_OR)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	if (count == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			clean_str = remove_quotes((*tokens)->value);
			if (!clean_str)
				clean_str = ft_strdup((*tokens)->value);
			argv[i++] = clean_str;
		}
		advance_token(tokens);
	}
	argv[i] = NULL;
	return (argv);
}

t_redir	*parse_redir(t_token **tokens)
{
	t_redir			*redir;
	t_token_type	type;
	char			*clean_file;

	if (!*tokens || ((*tokens)->type != TOKEN_REDIR_IN
			&& (*tokens)->type != TOKEN_REDIR_OUT
			&& (*tokens)->type != TOKEN_REDIR_APPEND
			&& (*tokens)->type != TOKEN_HEREDOC))
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	type = (*tokens)->type;
	advance_token(tokens);
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		free(redir);
		return (NULL);
	}
	redir->type = type;
	clean_file = remove_quotes((*tokens)->value);
	if (!clean_file)
		clean_file = ft_strdup((*tokens)->value);
	redir->file = clean_file;
	redir->next = NULL;
	advance_token(tokens);
	return (redir);
}

void	add_redir(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*current;

	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	current = *redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

t_token	*advance_token(t_token **tokens)
{
	if (*tokens)
		*tokens = (*tokens)->next;
	return (*tokens);
}

t_ast	*new_ast_node(t_ast_type type)
{
	t_ast *node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ast));
	node->type = type;
	return (node);
}