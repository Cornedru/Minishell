/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:13:22 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/27 20:26:35 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Creates a simple command node (a leaf of the tree)
t_ast	*create_cmd_node(char **args)
{
	t_ast	*node;

	node = (t_ast *)gc_malloc(sizeof(t_ast));
	node->type = AST_CMD;
	node->args = args; // The args array must also be from the GC
	node->filename = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// Creates an operator node (pipe, and, or)
t_ast	*create_op_node(t_ast_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = (t_ast *)gc_malloc(sizeof(t_ast));
	node->type = type;
	node->args = NULL;
	node->filename = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

// Creates a redirection node
t_ast	*create_redir_node(t_ast_type type, char *filename, t_ast *cmd_node)
{
	t_ast	*node;

	node = (t_ast *)gc_malloc(sizeof(t_ast));
	node->type = type;
	node->args = NULL;
	node->filename = filename; // The filename string must be from the GC
	node->left = cmd_node;
	node->right = NULL;
	return (node);
}

// ls -l
t_ast	*mock_ls_command(void)
{
	char	**ls_args;

	// The array of arguments MUST be NULL-terminated.
	ls_args = (char **)gc_malloc(sizeof(char *) * 3);
	ls_args[0] = gc_strdup("ls");
	ls_args[1] = gc_strdup("-l");
	ls_args[2] = NULL;

	return (create_cmd_node(ls_args));
}

// cat < input.txt
t_ast	*mock_redir_command(void)
{
	t_ast	*cmd_node;
	char	**cat_args;
	
	cat_args = (char **)gc_malloc(sizeof(char *) * 2);
	cat_args[0] = gc_strdup("cat");
	cat_args[1] = NULL;
	cmd_node = create_cmd_node(cat_args);
	
	// The redirection node wraps the command node.
	return (create_redir_node(AST_REDIR_IN, gc_strdup("input.txt"), cmd_node));
}

// ls -l | grep ".c"
t_ast	*mock_pipe_command(void)
{
	t_ast	*ls_node;
	t_ast	*grep_node;
	char	**ls_args;
	char	**grep_args;

	// Left side of the pipe
	ls_args = (char **)gc_malloc(sizeof(char *) * 3);
	ls_args[0] = gc_strdup("ls");
	ls_args[1] = gc_strdup("-l");
	ls_args[2] = NULL;
	ls_node = create_cmd_node(ls_args);

	// Right side of the pipe
	grep_args = (char **)gc_malloc(sizeof(char *) * 3);
	grep_args[0] = gc_strdup("grep");
	grep_args[1] = gc_strdup(".c");
	grep_args[2] = NULL;
	grep_node = create_cmd_node(grep_args);

	// The pipe node connects them.
	return (create_op_node(AST_PIPE, ls_node, grep_node));
}
