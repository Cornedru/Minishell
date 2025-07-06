#include "../../includes/minishell.h"

t_ast	*parse_redirections(t_token **tokens)
{
	t_ast	*first_redir;
	t_ast	*last_redir;
	t_ast	*new_redir;

	first_redir = NULL;
	last_redir = NULL;
	while (*tokens && is_redirection_token((*tokens)->type))
	{
		new_redir = parse_single_redirection(tokens);
		if (!new_redir)
		{
			free_ast(first_redir);
			return (NULL);
		}
		if (!first_redir)
			first_redir = new_redir;
		else
			last_redir->left = new_redir;
		last_redir = new_redir;
	}
	return (first_redir);
}

t_ast	*parse_single_redirection(t_token **tokens)
{
	t_ast_type	redir_type;
	t_token		*filename_token;
	t_ast		*node;

	if (!is_redirection_token((*tokens)->type))
		return (NULL);
	if ((*tokens)->type == TOKEN_REDIR_IN)
		redir_type = AST_REDIR_IN;
	else if ((*tokens)->type == TOKEN_REDIR_OUT)
		redir_type = AST_REDIR_OUT;
	else if ((*tokens)->type == TOKEN_REDIR_APPEND)
		redir_type = AST_REDIR_APPEND;
	else if ((*tokens)->type == TOKEN_HEREDOC)
		redir_type = AST_HEREDOC;
	else
		return (NULL);
	advance_token(tokens);
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error: expected filename after redirection\n",
			2);
		return (NULL);
	}
	filename_token = *tokens;
	advance_token(tokens);
	node = new_ast_node(redir_type);
	if (!node)
		return (NULL);
	node->filename = remove_quotes(filename_token->value);
	if (!node->filename)
		node->filename = gc_strdup(filename_token->value);
	return (node);
}

int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}
