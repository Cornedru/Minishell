/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/27 01:00:30 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	t_ast	*temp;

	if (!*tokens)
		return (NULL);
	cmd = NULL;
	redirs = collect_redirections_and_args(tokens, &cmd);
	if (!cmd && !redirs)
		return (NULL);
	if (!cmd && redirs)
	{
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
	if (redirs)
	{
		temp = redirs;
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
	// gc_free(line);
	return (ast);
}
