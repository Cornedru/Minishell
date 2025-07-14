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

// t_ast *parse_redirections(t_token **tokens)
// {
//     t_ast *redir_node;
//     char *filename;

//     if (!*tokens)
//         return NULL;

//     if ((*tokens)->type == TOKEN_REDIR_IN || (*tokens)->type == TOKEN_REDIR_OUT)
//     {
//         int redir_type = (*tokens)->type;
//         advance_token(tokens);  // avancer après le token de redirection

//         if (!*tokens || (*tokens)->type != TOKEN_WORD)
//         {
//             if (redir_type == TOKEN_REDIR_IN)
//                 ft_putstr_fd("minishell: syntax error: expected filename after redirection\n", 2);
//             else if (redir_type == TOKEN_REDIR_OUT)
//                 ft_putstr_fd("minishell: syntax error: expected filename after redirection\n", 2);
//             return NULL;
//         }

//         filename = remove_quotes((*tokens)->value);
//         advance_token(tokens);

//         redir_node = new_ast_node(redir_type == TOKEN_REDIR_IN ? AST_REDIR_IN : AST_REDIR_OUT);
//         if (!redir_node)
//             return NULL;
//         redir_node->filename = filename;
//         // Le fils gauche sera la commande ou redirection suivante
//         redir_node->left = parse_redirections(tokens);  // récursif pour plusieurs redirs
//         return redir_node;
//     }
//     return NULL;
// }

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
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
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

// t_ast *parse_single_redirection(t_token **tokens)
// {
//     t_ast_type redir_type;
//     t_token *filename_token;
//     t_ast *node;

//     if (!is_redirection_token((*tokens)->type))
//         return (NULL);

//     if ((*tokens)->type == TOKEN_REDIR_IN)
//         redir_type = AST_REDIR_IN;
//     else if ((*tokens)->type == TOKEN_REDIR_OUT)
//         redir_type = AST_REDIR_OUT;
//     else if ((*tokens)->type == TOKEN_REDIR_APPEND)
//         redir_type = AST_REDIR_APPEND;
//     else if ((*tokens)->type == TOKEN_HEREDOC)
//         redir_type = AST_HEREDOC;
//     else
//         return (NULL);

//     // Ne pas avancer ici, on vérifie d'abord le token suivant
//     t_token *next_token = (*tokens)->next; // ou selon ta structure, récupérer le token suivant

//     if (!next_token || next_token->type != TOKEN_WORD)
//     {
//         ft_putstr_fd("minishell: syntax error: expected filename after redirection\n", 2);
//         return (NULL);
//     }

//     // Maintenant on peut avancer le token d'origine et le filename
//     advance_token(tokens); // avance sur la redirection
//     advance_token(tokens); // avance sur le filename

//     filename_token = next_token;

//     node = new_ast_node(redir_type);
//     if (!node)
//         return (NULL);

//     node->filename = remove_quotes(filename_token->value);
//     if (!node->filename)
//         node->filename = gc_strdup(filename_token->value);

//     return (node);
// }



int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}
