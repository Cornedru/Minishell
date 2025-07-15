/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/06 06:04:23 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	**create_empty_argv(void)
// {
// 	char	**argv;

// 	argv = gc_malloc(sizeof(char *) * 2);
// 	if (argv)
// 	{
// 		argv[0] = gc_strdup("");
// 		argv[1] = NULL;
// 	}
// 	return (argv);
// }

int	init_command_node(t_ast **node)
{
	*node = new_ast_node(AST_CMD);
	if (!*node)
		return (0);
	(*node)->args = NULL;
	return (1);
}

int	skip_valid_redirections(t_token **tokens)
{
	while (*tokens && ((*tokens)->type == TOKEN_REDIR_IN
			|| (*tokens)->type == TOKEN_REDIR_OUT
			|| (*tokens)->type == TOKEN_REDIR_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC))
	{
		advance_token(tokens);
		if (!*tokens || (*tokens)->type != TOKEN_WORD)
			return (0);
		advance_token(tokens);
	}
	return (1);
}

int	is_invalid_pipe(t_token **tokens)
{
	return (!*tokens || (*tokens)->type == TOKEN_PIPE);
}

t_ast	*handle_pipeline_right(t_ast *left, t_token **tokens)
{
	t_ast	*right;
	t_ast	*new_node;

	right = parse_command(tokens);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	new_node = create_pipeline_node(left, right);
	if (!new_node)
	{
		free_ast(right);
		return (NULL);
	}
	return (new_node);
}
