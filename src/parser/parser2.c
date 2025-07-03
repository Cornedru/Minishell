/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 07:43:00 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**create_empty_argv(void)
{
	char	**argv;

	argv = gc_malloc(sizeof(char *) * 2);
	if (argv)
	{
		argv[0] = gc_strdup("");
		argv[1] = NULL;
	}
	return (argv);
}

static int	init_command_node(t_ast **node)
{
	*node = new_ast_node(AST_CMD);
	if (!*node)
		return (0);
	(*node)->args = NULL;
	return (1);
}

// t_ast	*parse_simple_command(t_token **tokens)
// {
// 	t_ast	*node;
// 	t_token	*start;

// 	if (!init_command_node(&node))
// 		return (NULL);
// 	start = *tokens;
// 	while (*tokens && ((*tokens)->type == TOKEN_REDIR_IN
// 			|| (*tokens)->type == TOKEN_REDIR_OUT
// 			|| (*tokens)->type == TOKEN_REDIR_APPEND
// 			|| (*tokens)->type == TOKEN_HEREDOC))
// 	{
// 		advance_token(tokens);
// 		if (!*tokens || (*tokens)->type != TOKEN_WORD)
// 		{
// 			free_ast(node);
// 			return (NULL);
// 		}
// 		advance_token(tokens);
// 	}
// 	*tokens = start;
// 	node->args = gather_all_words(tokens);
// 	if (!node->args)
// 		node->args = create_empty_argv();
// 	if (!node->args)
// 	{
// 		free_ast(node);
// 		return (NULL);
// 	}
// 	return (node);
// }

static int	skip_valid_redirections(t_token **tokens)
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

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	t_token	*start;

	if (!init_command_node(&node))
		return (NULL);
	start = *tokens;
	if (!skip_valid_redirections(tokens))
		return (free_ast(node), NULL);
	*tokens = start;
	node->args = gather_all_words(tokens);
	if (!node->args)
		node->args = create_empty_argv();
	if (!node->args)
		return (free_ast(node), NULL);
	return (node);
}

t_ast	*parse_command(t_token **tokens)
{
	if (!*tokens)
		return (NULL);
	return (parse_simple_command(tokens));
}

// t_ast	*parse_pipeline(t_token **tokens)
// {
// 	t_ast	*left;
// 	t_ast	*right;

// 	left = parse_command(tokens);
// 	if (!left)
// 		return (NULL);
// 	if (!*tokens || (*tokens)->type != TOKEN_PIPE)
// 		return (left);
// 	advance_token(tokens);
// 	right = parse_pipeline(tokens);
// 	if (!right)
// 	{
// 		free_ast(left);
// 		return (NULL);
// 	}
// 	return (create_pipeline_node(left, right));
// }

// t_ast *parse_pipeline(t_token **tokens)
// {
//     t_ast *left;
//     t_ast *right;

//     left = parse_command(tokens);
//     if (!left)
//         return (NULL);
//     if (!*tokens || (*tokens)->type != TOKEN_PIPE)
//         return (left);
//     advance_token(tokens);
//     right = parse_pipeline(tokens);
//     if (!right)
//     {
//         free_ast(left);
//         return (NULL); // erreur : pipe sans commande après
//     }
//     return (create_pipeline_node(left, right));
// }

// t_ast	*parse_pipeline(t_token **tokens)
// {
// 	t_ast	*left;
// 	t_ast	*right;

// 	if (!tokens || !*tokens)
// 		return (NULL);
// 	if ((*tokens)->type == TOKEN_PIPE)
// 		return (NULL);
// 	left = parse_command(tokens);
// 	if (!left)
// 		return (NULL);
// 	while (*tokens && (*tokens)->type == TOKEN_PIPE)
// 	{
// 		advance_token(tokens);
// 		if (!*tokens || (*tokens)->type == TOKEN_PIPE)
// 		{
// 			free_ast(left);
// 			return (NULL);
// 		}
// 		right = parse_command(tokens);
// 		if (!right)
// 		{
// 			free_ast(left);
// 			return (NULL);
// 		}
// 		left = create_pipeline_node(left, right);
// 		if (!left)
// 		{
// 			free_ast(right);
// 			return (NULL);
// 		}
// 	}
// 	return (left);
// }

static int	is_invalid_pipe(t_token **tokens)
{
	return (!*tokens || (*tokens)->type == TOKEN_PIPE);
}

static t_ast	*handle_pipeline_right(t_ast *left, t_token **tokens)
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

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;

	if (!tokens || is_invalid_pipe(tokens))
		return (NULL);
	left = parse_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		advance_token(tokens);
		if (is_invalid_pipe(tokens))
			return (free_ast(left), NULL);
		left = handle_pipeline_right(left, tokens);
		if (!left)
			return (NULL);
	}
	return (left);
}
