/* parser.c */
#include "minishell.h"

/* Grammaire simplifiée :
 * line        → pipeline (('&&' | '||') pipeline)*
 * pipeline    → command ('|' command)*
 * command     → word* redirection*
 * redirection → ('<' | '>' | '>>' | '<<') word
 */

static t_token	*advance_token(t_token **tokens)
{
	if (*tokens)
		*tokens = (*tokens)->next;
	return (*tokens);
}

static t_ast	*new_ast_node(t_ast_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ast));
	node->type = type;
	return (node);
}

static char	**tokens_to_argv(t_token **tokens)
{
	int		count;
	t_token	*tmp;
	char	**argv;
	int		i;

	count = 0;
	tmp = *tokens;
	i = 0;
	/* Count words */
	while (tmp && tmp->type == TOKEN_WORD)
	{
		count++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	/* Fill argv */
	while (i < count && (*tokens)->type == TOKEN_WORD)
	{
		argv[i] = ft_strdup((*tokens)->value);
		advance_token(tokens);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static t_redir	*parse_redirection(t_token **tokens)
{
	t_redir			*redir;
	t_redir_type	type;

	if (!*tokens)
		return (NULL);
	/* Determine redirection type */
	if ((*tokens)->type == TOKEN_REDIR_IN)
		type = REDIR_IN;
	else if ((*tokens)->type == TOKEN_REDIR_OUT)
		type = REDIR_OUT;
	else if ((*tokens)->type == TOKEN_REDIR_APPEND)
		type = REDIR_APPEND;
	else if ((*tokens)->type == TOKEN_HEREDOC)
		type = REDIR_HEREDOC;
	else
		return (NULL);
	advance_token(tokens); /* Skip operator */
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (NULL); /* Syntax error */
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup((*tokens)->value);
	redir->fd = -1;
	redir->next = NULL;
	advance_token(tokens); /* Skip filename */
	return (redir);
}

static t_ast	*parse_command(t_token **tokens)
{
	t_ast	*node;
	t_redir	*redir;
	t_redir	*last_redir;

	last_redir = NULL;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (NULL);
	node = new_ast_node(AST_COMMAND);
	if (!node)
		return (NULL);
	/* Parse arguments */
	node->argv = tokens_to_argv(tokens);
	/* Parse redirections */
	while (*tokens && ((*tokens)->type == TOKEN_REDIR_IN
			|| (*tokens)->type == TOKEN_REDIR_OUT
			|| (*tokens)->type == TOKEN_REDIR_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC))
	{
		redir = parse_redirection(tokens);
		if (!redir)
		{
			free_ast(node);
			return (NULL);
		}
		if (!node->redirs)
			node->redirs = redir;
		else
			last_redir->next = redir;
		last_redir = redir;
	}
	return (node);
}

static t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*pipe_node;

	left = parse_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		advance_token(tokens); /* Skip '|' */
		pipe_node = new_ast_node(AST_PIPELINE);
		if (!pipe_node)
		{
			free_ast(left);
			return (NULL);
		}
		pipe_node->left = left;
		pipe_node->right = parse_command(tokens);
		if (!pipe_node->right)
		{
			free_ast(pipe_node);
			return (NULL);
		}
		left = pipe_node;
	}
	return (left);
}

t_ast	*parse(t_token **tokens)
{
	t_ast *left = parse_pipeline(tokens);
	t_ast *logical_node;

	if (!left)
		return (NULL);

	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		t_token_type op = (*tokens)->type;
		advance_token(tokens); /* Skip '&&' or '||' */

		logical_node = new_ast_node((op == TOKEN_AND) ? AST_AND : AST_OR);
		if (!logical_node)
		{
			free_ast(left);
			return (NULL);
		}

		logical_node->left = left;
		logical_node->right = parse_pipeline(tokens);

		if (!logical_node->right)
		{
			free_ast(logical_node);
			return (NULL);
		}

		left = logical_node;
	}

	return (left);
}