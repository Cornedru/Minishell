// #include "../minishell.h"
// #include "../libft/libft.h"

// static t_token	*advance_token(t_token **tokens)
// {
// 	if (*tokens)
// 		*tokens = (*tokens)->next;
// 	return (*tokens);
// }

// static t_ast	*new_ast_node(t_node_type type)
// {
// 	t_ast *node = malloc(sizeof(t_ast));
// 	if (!node)
// 		return (NULL);
// 	node->type = type;
// 	node->args = NULL;
// 	node->redir_file = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// static char	**token_list_to_args(t_token *tokens)
// {
// 	int		count = 0;
// 	char	**args;
// 	t_token *tmp = tokens;
// 	int		i = 0;

// 	while (tmp && tmp->type == TOKEN_WORD)
// 	{
// 		count++;
// 		tmp = tmp->next;
// 	}
// 	args = malloc(sizeof(char *) * (count + 1));
// 	if (!args)
// 		return (NULL);
// 	tmp = tokens;
// 	while (i < count)
// 	{
// 		args[i] = ft_strdup(tmp->value);
// 		if (!args[i])
// 		{
// 			while (i > 0)
// 				free(args[--i]);
// 			free(args);
// 			return (NULL);
// 		}
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }

// /*
// 	Parse command simple, sans pipe, sans redirection complexe
// 	Format : WORD [WORD ...]
// 	Retourne un AST NODE_CMD avec args
// */
// static t_ast	*parse_simple_command(t_token **tokens)
// {
// 	t_ast	*node;
// 	t_token	*start = *tokens;
// 	int		count = 0;

// 	// count words
// 	while (*tokens && (*tokens)->type == TOKEN_WORD)
// 	{
// 		count++;
// 		advance_token(tokens);
// 	}
// 	if (count == 0)
// 		return (NULL);
// 	node = new_ast_node(NODE_CMD);
// 	if (!node)
// 		return (NULL);
// 	node->args = token_list_to_args(start);
// 	return (node);
// }

// /*
// 	Parse redirection type :
// 	< file, > file, >> file, << limiter
// */
// static int	parse_redirection(t_token **tokens, t_ast **redir_node)
// {
// 	t_token_type type = (*tokens)->type;
// 	advance_token(tokens); // consume operator

// 	if (!*tokens || (*tokens)->type != TOKEN_WORD)
// 		return (-1); // syntax error

// 	t_ast *node = new_ast_node(
// 		(type == TOKEN_REDIR_IN) ? NODE_REDIR_IN :
// 		(type == TOKEN_REDIR_OUT) ? NODE_REDIR_OUT :
// 		(type == TOKEN_REDIR_APPEND) ? NODE_REDIR_APPEND :
// 		NODE_HEREDOC);

// 	if (!node)
// 		return (-1);

// 	node->redir_file = ft_strdup((*tokens)->value);
// 	if (!node->redir_file)
// 	{
// 		free_ast(node);
// 		return (-1);
// 	}
// 	advance_token(tokens); // consume filename
// 	*redir_node = node;
// 	return (0);
// }

// /*
// 	Parse command with optional redirections
// */
// static t_ast	*parse_command_with_redir(t_token **tokens)
// {
// 	t_ast *cmd = parse_simple_command(tokens);
// 	t_ast *redir;

// 	if (!cmd)
// 		return (NULL);

// 	while (*tokens && ((*tokens)->type == TOKEN_REDIR_IN ||
// 			(*tokens)->type == TOKEN_REDIR_OUT ||
// 			(*tokens)->type == TOKEN_REDIR_APPEND ||
// 			(*tokens)->type == TOKEN_HEREDOC))
// 	{
// 		if (parse_redirection(tokens, &redir) == -1)
// 		{
// 			free_ast(cmd);
// 			return (NULL);
// 		}
// 		// On ajoute la redirection dans l'AST,
// on peut chaîner les redirs à droite
// 		t_ast *redir_root = new_ast_node(redir->type);
// 		if (!redir_root)
// 		{
// 			free_ast(cmd);
// 			free_ast(redir);
// 			return (NULL);
// 		}
// 		redir_root->redir_file = ft_strdup(redir->redir_file);
// 		free_ast(redir);
// 		redir_root->left = cmd;
// 		cmd = redir_root;
// 	}

// 	return (cmd);
// }

// /*
// 	Parse parenthese : ( ... )
// */
// static t_ast	*parse_subshell(t_token **tokens)
// {
// 	if (!*tokens || (*tokens)->type != TOKEN_LPAREN)
// 		return (NULL);
// 	advance_token(tokens); // consume '('
// 	t_ast *node = parse(tokens);
// 	if (!node)
// 		return (NULL);
// 	if (!*tokens || (*tokens)->type != TOKEN_RPAREN)
// 	{
// 		free_ast(node);
// 		return (NULL);
// 	}
// 	advance_token(tokens); // consume ')'
// 	t_ast *subshell_node = new_ast_node(NODE_SUBSHELL);
// 	if (!subshell_node)
// 	{
// 		free_ast(node);
// 		return (NULL);
// 	}
// 	subshell_node->left = node;
// 	return (subshell_node);
// }

// /*
// 	Parse factor : either a subshell or a command with redirections
// */
// static t_ast	*parse_factor(t_token **tokens)
// {
// 	if (!*tokens)
// 		return (NULL);
// 	if ((*tokens)->type == TOKEN_LPAREN)
// 		return (parse_subshell(tokens));
// 	else if ((*tokens)->type == TOKEN_WORD)
// 		return (parse_command_with_redir(tokens));
// 	return (NULL);
// }

// /*
// 	Parse pipeline : factor { | factor }
// */
// static t_ast	*parse_pipeline(t_token **tokens)
// {
// 	t_ast *left = parse_factor(tokens);
// 	if (!left)
// 		return (NULL);

// 	while (*tokens && (*tokens)->type == TOKEN_PIPE)
// 	{
// 		advance_token(tokens); // consume '|'
// 		t_ast *right = parse_factor(tokens);
// 		if (!right)
// 		{
// 			free_ast(left);
// 			return (NULL);
// 		}
// 		t_ast *pipe_node = new_ast_node(NODE_PIPE);
// 		if (!pipe_node)
// 		{
// 			free_ast(left);
// 			free_ast(right);
// 			return (NULL);
// 		}
// 		pipe_node->left = left;
// 		pipe_node->right = right;
// 		left = pipe_node;
// 	}
// 	return (left);
// }

// /*
// 	Parse logical AND/OR : pipeline { && pipeline | || pipeline }
// */
// static t_ast	*parse_logical(t_token **tokens)
// {
// 	t_ast *left = parse_pipeline(tokens);
// 	if (!left)
// 		return (NULL);

// 	while (*tokens && ((*tokens)->type == TOKEN_AND
// || (*tokens)->type == TOKEN_OR))
// 	{
// 		t_token_type op = (*tokens)->type;
// 		advance_token(tokens); // consume && or ||
// 		t_ast *right = parse_pipeline(tokens);
// 		if (!right)
// 		{
// 			free_ast(left);
// 			return (NULL);
// 		}
// 		t_ast *node = new_ast_node((op == TOKEN_AND) ? NODE_AND : NODE_OR);
// 		if (!node)
// 		{
// 			free_ast(left);
// 			free_ast(right);
// 			return (NULL);
// 		}
// 		node->left = left;
// 		node->right = right;
// 		left = node;
// 	}
// 	return (left);
// }

// /*
// 	Entry point parse
// */
// t_ast	*parse(t_token **tokens)
// {
// 	if (!tokens || !*tokens)
// 		return (NULL);
// 	return (parse_logical(tokens));
// }

// void	free_ast(t_ast *ast)
// {
// 	int i;

// 	if (!ast)
// 		return ;
// 	if (ast->args)
// 	{
// 		for (i = 0; ast->args[i]; i++)
// 			free(ast->args[i]);
// 		free(ast->args);
// 	}
// 	if (ast->redir_file)
// 		free(ast->redir_file);
// 	if (ast->left)
// 		free_ast(ast->left);
// 	if (ast->right)
// 		free_ast(ast->right);
// 	free(ast);
// }

// static void	print_indent(int depth)
// {
// 	while (depth-- > 0)
// 		printf("  ");
// }

// void	print_ast(t_ast *ast, int depth)
// {
// 	int i;

// 	if (!ast)
// 		return ;
// 	print_indent(depth);
// 	switch (ast->type)
// 	{
// 		case NODE_CMD:
// 			printf("CMD:");
// 			if (ast->args)
// 			{
// 				for (i = 0; ast->args[i]; i++)
// 					printf(" %s", ast->args[i]);
// 			}
// 			printf("\n");
// 			break ;
// 		case NODE_PIPE:
// 			printf("PIPE\n");
// 			print_ast(ast->left, depth + 1);
// 			print_ast(ast->right, depth + 1);
// 			break ;
// 		case NODE_AND:
// 			printf("AND\n");
// 			print_ast(ast->left, depth + 1);
// 			print_ast(ast->right, depth + 1);
// 			break ;
// 		case NODE_OR:
// 			printf("OR\n");
// 			print_ast(ast->left, depth + 1);
// 			print_ast(ast->right, depth + 1);
// 			break ;
// 		case NODE_REDIR_IN:
// 			printf("REDIR_IN: %s\n", ast->redir_file);
// 			print_ast(ast->left, depth + 1);
// 			break ;
// 		case NODE_REDIR_OUT:
// 			printf("REDIR_OUT: %s\n", ast->redir_file);
// 			print_ast(ast->left, depth + 1);
// 			break ;
// 		case NODE_REDIR_APPEND:
// 			printf("REDIR_APPEND: %s\n", ast->redir_file);
// 			print_ast(ast->left, depth + 1);
// 			break ;
// 		case NODE_HEREDOC:
// 			printf("HEREDOC: %s\n", ast->redir_file);
// 			print_ast(ast->left, depth + 1);
// 			break ;
// 		case NODE_SUBSHELL:
// 			printf("SUBSHELL\n");
// 			print_ast(ast->left, depth + 1);
// 			break ;
// 		default:
// 			printf("UNKNOWN NODE\n");
// 	}
// }
