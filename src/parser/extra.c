// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   extra.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
// /*   Updated: 2025/07/15 01:26:31 by ndehmej          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// // t_ast	*parse_simple_command(t_token **tokens)
// // {
// // 	t_ast	*node;
// // 	t_token	*start;

// // 	if (!init_command_node(&node))
// // 		return (NULL);
// // 	start = *tokens;
// // 	if (!skip_valid_redirections(tokens))
// // 		return (free_ast(node), NULL);
// // 	*tokens = start;
// // 	node->args = gather_all_words(tokens);
// // 	if (!node->args)
// // 		node->args = create_empty_argv();
// // 	if (!node->args)
// // 		return (free_ast(node), NULL);
// // 	return (node);
// // }
// /* Version simplifiée de parse_simple_command qui respecte la norme */

// static int	count_consecutive_words(t_token *tokens)
// {
// 	int	count;

// 	count = 0;
// 	while (tokens && tokens->type == TOKEN_WORD)
// 	{
// 		count++;
// 		tokens = tokens->next;
// 	}
// 	return (count);
// }

// t_ast	*parse_simple_command(t_token **tokens)
// {
// 	t_ast	*node;
// 	char	**args;
// 	int		count;
// 	int		i;

// 	if (!*tokens || (*tokens)->type != TOKEN_WORD)
// 		return (NULL);
// 	count = count_consecutive_words(*tokens);
// 	node = new_ast_node(AST_CMD);
// 	if (!node)
// 		return (NULL);
// 	args = (char **)gc_malloc(sizeof(char *) * (count + 1));
// 	if (!args)
// 		return (free_ast(node), NULL);
// 	i = 0;
// 	while (*tokens && (*tokens)->type == TOKEN_WORD && i < count)
// 	{
// 		args[i] = remove_quotes((*tokens)->value);
// 		if (!args[i])
// 			args[i] = gc_strdup((*tokens)->value);
// 		advance_token(tokens);
// 		i++;
// 	}
// 	args[i] = NULL;
// 	node->args = args;
// 	return (node);
// }
// t_ast	*parse_command(t_token **tokens)
// {
// 	t_ast	*cmd;
// 	t_ast	*initial_redir;

// 	if (!*tokens)
// 		return (NULL);
// 	initial_redir = NULL;
// 	if (is_redirection_token((*tokens)->type))
// 	{
// 		initial_redir = parse_redirections(tokens);
// 		if (!initial_redir)
// 			return (NULL);
// 	}
// 	cmd = parse_simple_command(tokens);
// 	if (!cmd && !initial_redir)
// 		return (NULL);
// 	if (!cmd)
// 		return (initial_redir);
// 	if (!parse_remaining_tokens(tokens, &cmd))
// 	{
// 		free_ast(cmd);
// 		free_ast(initial_redir);
// 		return (NULL);
// 	}
// 	return (attach_redirections(cmd, initial_redir));
// }

// t_ast	*parse_pipeline(t_token **tokens)
// {
// 	t_ast	*left;
// 	t_ast	*right;

// 	if (*tokens && (*tokens)->type == TOKEN_PIPE)
// 	{
// 		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
// 		return (NULL);
// 	}
// 	left = parse_command(tokens);
// 	if (!left)
// 		return (NULL);
// 	while (*tokens && (*tokens)->type == TOKEN_PIPE)
// 	{
// 		advance_token(tokens);
// 		if (!*tokens || (*tokens)->type == TOKEN_PIPE)
// 		{
// 			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
// 				2);
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
// 			return (NULL);
// 	}
// 	return (left);
// }

// char	*process_segment(char *str, int *i, int seg_start, t_sys *sys)
// {
// 	char	*temp;
// 	char	*var_value;
// 	char	*result;

// 	result = gc_strdup("");
// 	if (*i > seg_start)
// 	{
// 		temp = gc_substr(str, seg_start, *i - seg_start);
// 		result = gc_strjoin_free_s1(result, temp);
// 	}
// 	if (*i < (int)ft_strlen(str) && str[*i] == '$')
// 	{
// 		var_value = expand_variable(str, i, sys);
// 		result = gc_strjoin_free_s1(result, var_value);
// 	}
// 	return (result);
// }

// /* Version mise à jour de parse_line avec validation de syntaxe */

// t_ast	*parse_line(char *line, t_sys *sys)
// {
// 	t_token	*tokens;
// 	t_ast	*ast;

// 	if (!are_quotes_closed(line))
// 	{
// 		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
// 		return (NULL);
// 	}
// 	tokens = lexer(line);
// 	if (!tokens)
// 		return (NULL);
// 	expand_tokens(tokens, sys);
// 	if (!validate_syntax(tokens))
// 	{
// 		free_tokens(tokens);
// 		return (NULL);
// 	}
// 	ast = parse(&tokens);
// 	free_tokens(tokens);
// 	return (ast);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/15 01:26:31 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Déclaration de la fonction depuis extra2.c */
char	**merge_args(char **old_args, char **new_args);

static int	count_consecutive_words(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type == TOKEN_WORD)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	char	**args;
	int		count;
	int		i;

	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (NULL);
	count = count_consecutive_words(*tokens);
	node = new_ast_node(AST_CMD);
	if (!node)
		return (NULL);
	args = (char **)gc_malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (free_ast(node), NULL);
	i = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD && i < count)
	{
		args[i] = remove_quotes((*tokens)->value);
		if (!args[i])
			args[i] = gc_strdup((*tokens)->value);
		advance_token(tokens);
		i++;
	}
	args[i] = NULL;
	node->args = args;
	return (node);
}

static t_ast	*collect_redirections_and_args(t_token **tokens, t_ast **cmd)
{
	t_ast	*redirs;
	t_ast	*last_redir;
	t_ast	*new_redir;

	redirs = NULL;
	last_redir = NULL;
	*cmd = NULL;
	
	while (*tokens && (*tokens)->type != TOKEN_PIPE 
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if (is_redirection_token((*tokens)->type))
		{
			new_redir = parse_single_redirection(tokens);
			if (!new_redir)
			{
				free_ast(redirs);
				free_ast(*cmd);
				return (NULL);
			}
			if (!redirs)
				redirs = new_redir;
			else
			{
				last_redir = redirs;
				while (last_redir->left)
					last_redir = last_redir->left;
				last_redir->left = new_redir;
			}
		}
		else if ((*tokens)->type == TOKEN_WORD)
		{
			if (!*cmd)
			{
				*cmd = parse_simple_command(tokens);
				if (!*cmd)
				{
					free_ast(redirs);
					return (NULL);
				}
			}
			else
			{
				// Ajouter des arguments supplémentaires à la commande existante
				char **additional_args = gather_all_words(tokens);
				if (additional_args && additional_args[0])
				{
					(*cmd)->args = merge_args((*cmd)->args, additional_args);
					if (!(*cmd)->args)
					{
						free_ast(redirs);
						free_ast(*cmd);
						return (NULL);
					}
				}
			}
		}
		else
			break;
	}
	
	return (redirs);
}

char	**create_empty_argv(void)
{
	char	**argv;

	argv = (char **)gc_malloc(sizeof(char *) * 2);
	if (argv)
	{
		argv[0] = gc_strdup("");
		argv[1] = NULL;
	}
	return (argv);
}

t_ast	*parse_command(t_token **tokens)
{
	t_ast	*cmd;
	t_ast	*redirs;

	if (!*tokens)
		return (NULL);
	
	cmd = NULL;
	redirs = collect_redirections_and_args(tokens, &cmd);
	
	// Si on n'a ni commande ni redirections, erreur
	if (!cmd && !redirs)
		return (NULL);
	
	// Si on a seulement des redirections sans commande
	if (!cmd && redirs)
	{
		// Créer une commande vide
		cmd = new_ast_node(AST_CMD);
		if (!cmd)
		{
			free_ast(redirs);
			return (NULL);
		}
		cmd->args = create_empty_argv();
		if (!cmd->args)
		{
			free_ast(cmd);
			free_ast(redirs);
			return (NULL);
		}
	}
	
	// Attacher les redirections à la commande
	if (redirs)
	{
		t_ast *temp = redirs;
		while (temp->left)
			temp = temp->left;
		temp->left = cmd;
		return (redirs);
	}
	
	return (cmd);
}

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;

	if (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (NULL);
	}
	left = parse_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		advance_token(tokens);
		if (!*tokens || (*tokens)->type == TOKEN_PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
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
			return (NULL);
	}
	return (left);
}

char	*process_segment(char *str, int *i, int seg_start, t_sys *sys)
{
	char	*temp;
	char	*var_value;
	char	*result;

	result = gc_strdup("");
	if (*i > seg_start)
	{
		temp = gc_substr(str, seg_start, *i - seg_start);
		result = gc_strjoin_free_s1(result, temp);
	}
	if (*i < (int)ft_strlen(str) && str[*i] == '$')
	{
		var_value = expand_variable(str, i, sys);
		result = gc_strjoin_free_s1(result, var_value);
	}
	return (result);
}

t_ast	*parse_line(char *line, t_sys *sys)
{
	t_token	*tokens;
	t_ast	*ast;

	if (!are_quotes_closed(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		return (NULL);
	}
	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	expand_tokens(tokens, sys);
	if (!validate_syntax(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	ast = parse(&tokens);
	free_tokens(tokens);
	return (ast);
}