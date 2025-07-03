/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 07:31:17 by ndehmej          ###   ########.fr       */
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
		
// 		if (*tokens && (*tokens)->type == TOKEN_WORD)
// 			advance_token(tokens);
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
t_ast *parse_simple_command(t_token **tokens)
{
    t_ast   *node;
    t_token *start;

    if (!init_command_node(&node))
        return (NULL);
    start = *tokens;
    while (*tokens && ((*tokens)->type == TOKEN_REDIR_IN
            || (*tokens)->type == TOKEN_REDIR_OUT
            || (*tokens)->type == TOKEN_REDIR_APPEND
            || (*tokens)->type == TOKEN_HEREDOC))
    {
        advance_token(tokens);
        // Vérifie que le token suivant est un mot (fichier)
        if (!*tokens || (*tokens)->type != TOKEN_WORD)
        {
            free_ast(node);
            return (NULL); // erreur de syntaxe : redirection sans fichier
        }
        advance_token(tokens);
    }
    *tokens = start;
    node->args = gather_all_words(tokens);
    if (!node->args)
        node->args = create_empty_argv();
    if (!node->args)
    {
        free_ast(node);
        return (NULL);
    }
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

t_ast *parse_pipeline(t_token **tokens)
{
    t_ast *left;
    t_ast *right;

    if (!tokens || !*tokens)
        return (NULL);

    if ((*tokens)->type == TOKEN_PIPE)
        return (NULL);
    left = parse_command(tokens);
    if (!left)
        return (NULL);
    while (*tokens && (*tokens)->type == TOKEN_PIPE)
    {
        advance_token(tokens);
        if (!*tokens || (*tokens)->type == TOKEN_PIPE)
        {
            free_ast(left);
            return (NULL);
        }
        right = parse_command(tokens);
        if (!right)
        {
            free_ast(left);
            return (NULL);
        }
        left = create_pipeline_node(left, right);
        if (!left)
        {
            free_ast(right);
            return (NULL);
        }
    }
    return (left);
}
