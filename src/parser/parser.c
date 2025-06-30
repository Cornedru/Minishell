/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/30 02:10:55 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//

// int	count_word_tokens(t_token *tokens)
// {
// 	int		count;
// 	t_token	*tmp;

// 	count = 0;
// 	tmp = tokens;
// 	while (tmp && tmp->type == TOKEN_WORD)
// 	{
// 		count++;
// 		tmp = tmp->next;
// 	}
// 	return (count);
// }

//

// char	**tokens_to_argv(t_token **tokens)
// {
// 	int		count;
// 	char	**argv;
// 	int		i;
// 	char	*clean_str;

// 	count = count_word_tokens(*tokens);
// 	if (count == 0)
// 		return (NULL);
// 	argv = malloc(sizeof(char *) * (count + 1));
// 	if (!argv)
// 		return (NULL);
// 	i = 0;
// 	while (i < count && (*tokens) && (*tokens)->type == TOKEN_WORD)
// 	{
// 		// Remove quotes from the token value
// 		clean_str = remove_quotes((*tokens)->value);
// 		if (!clean_str)
// 			clean_str = ft_strdup((*tokens)->value);
// 		argv[i] = clean_str;
// 		if (!argv[i])
// 		{
// 			ft_free_split(argv);
// 			return (NULL);
// 		}
// 		advance_token(tokens);
// 		i++;
// 	}
// 	argv[i] = NULL;
// 	return (argv);
// }

// int count_word(t_token	*tokens)
// {
// 	int count;
// 	t_token *tmp;

// 	count = 0;
// 	tmp = tokens;
// 	while(tmp && tmp->type == TOKEN_WORD)
// 	{
// 		count++;
// 		tmp = tmp->next;
// 	}
// 	return (count);
// }

// char **tokens_to_av(t_token **tokens)
// {
// 	int count;

// 	count = count_word(*tokens);
// 	if (count = 0)
// 		return (NULL);

// }

static t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	t_redir	*redir;
	t_token	*start;

	node = new_ast_node(AST_COMMAND);
	if (!node)
		return (NULL);
	node->redirs = NULL;
	node->argv = NULL;
	start = *tokens;
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if ((*tokens)->type == TOKEN_REDIR_IN
			|| (*tokens)->type == TOKEN_REDIR_OUT
			|| (*tokens)->type == TOKEN_REDIR_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC)
		{
			redir = parse_redir(tokens);
			if (redir)
				add_redir(&node->redirs, redir);
			else
			{
				free_ast(node);
				return (NULL);
			}
		}
		else
			advance_token(tokens);
	}
	*tokens = start;
	node->argv = gather_all_words(tokens);
	if (!node->argv && node->redirs)
	{
		node->argv = malloc(sizeof(char *) * 2);
		if (node->argv)
		{
			node->argv[0] = ft_strdup("");
			node->argv[1] = NULL;
		}
	}
	if (!node->argv)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}

static t_ast	*parse_command(t_token **tokens)
{
	if (!*tokens)
		return (NULL);
	return (parse_simple_command(tokens));
}

static t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*pipeline;

	left = parse_command(tokens);
	if (!left)
		return (NULL);
	if (!*tokens || (*tokens)->type != TOKEN_PIPE)
		return (left);
	advance_token(tokens);
	right = parse_pipeline(tokens);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	pipeline = new_ast_node(AST_PIPELINE);
	if (!pipeline)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	pipeline->left = left;
	pipeline->right = right;
	return (pipeline);
}

static t_ast	*parse_and_or(t_token **tokens)
{
	t_ast		*left;
	t_ast		*right;
	t_ast		*node;
	t_ast_type	type;

	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	if (!*tokens || ((*tokens)->type != TOKEN_AND
			&& (*tokens)->type != TOKEN_OR))
		return (left);
	if ((*tokens)->type == TOKEN_AND)
		type = AST_AND;
	else
		type = AST_OR;
	advance_token(tokens);
	right = parse_and_or(tokens);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	node = new_ast_node(type);
	if (!node)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type == TOKEN_WORD && ft_strcmp((*tokens)->value,
			"clear") == 0)
	{
		ft_clear();
		free((*tokens)->value);
		return (parse_and_or(tokens));
	}
	return (parse_and_or(tokens));
}
