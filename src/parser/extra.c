/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/06 07:46:23 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_ast	*parse_simple_command(t_token **tokens)
// {
// 	t_ast	*node;
// 	t_token	*start;

// 	if (!init_command_node(&node))
// 		return (NULL);
// 	start = *tokens;
// 	if (!skip_valid_redirections(tokens))
// 		return (free_ast(node), NULL);
// 	*tokens = start;
// 	node->args = gather_all_words(tokens);
// 	if (!node->args)
// 		node->args = create_empty_argv();
// 	if (!node->args)
// 		return (free_ast(node), NULL);
// 	return (node);
// }

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	char	**args;
	int		arg_count;
	int		i;
	t_token	*temp;

	arg_count = 0;
	temp = *tokens;
	while (temp && temp->type == TOKEN_WORD)
	{
		arg_count++;
		temp = temp->next;
	}
	if (arg_count == 0)
		return (NULL);
	node = new_ast_node(AST_CMD);
	if (!node)
		return (NULL);
	args = (char **)gc_malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
	{
		free_ast(node);
		return (NULL);
	}
	i = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD && i < arg_count)
	{
		args[i] = remove_quotes((*tokens)->value);
		if (!args[i])
			args[i] = gc_strdup((*tokens)->value);
		i++;
		advance_token(tokens);
	}
	args[i] = NULL;
	node->args = args;
	return (node);
}

t_ast	*parse_command(t_token **tokens)
{
	t_ast	*cmd;
	t_ast	*redir;
	t_ast	*post_redir;
	t_ast	*temp;

	
	
	if (!*tokens)
		return (NULL);

	t_token *start_token = *tokens;
	redir = parse_redirections(tokens);
	if (redir == NULL && start_token && is_redirection_token(start_token->type))
        return (NULL);
	
	cmd = parse_simple_command(tokens);
	if (!cmd && !redir)
		return (NULL);
	if (cmd)
	{
		post_redir = parse_redirections(tokens);
		if (post_redir)
		{
			temp = post_redir;
			while (temp->left)
				temp = temp->left;
			temp->left = cmd;
			cmd = post_redir;
		}
	}
	if (redir && cmd)
	{
		temp = redir;
		while (temp->left)
			temp = temp->left;
		temp->left = cmd;
		return (redir);
	}
	else if (redir)
		return (redir);
	else
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

int is_operator_token(int token_type)
{
    return (token_type == TOKEN_PIPE
         || token_type == TOKEN_AND
         || token_type == TOKEN_OR);
}

int validate_syntax(t_token *tokens)
{
    t_token *prev = NULL;
    t_token *curr = tokens;

    while (curr)
    {
        // 1) Vérifie redirection suivie d'un TOKEN_WORD
        if (is_redirection_token(curr->type))
        {
            if (!curr->next || curr->next->type != TOKEN_WORD)
            {
                ft_putstr_fd("minishell: syntax error: expected filename after redirection\n", 2);
                return 1;
            }
        }

        // 2) Vérifie opérateurs consécutifs invalides
        if (is_operator_token(curr->type))
        {
            if (prev && is_operator_token(prev->type))
            {
                ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
                return 1;
            }
            if (!curr->next) // opérateur en fin de ligne
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
                return 1;
            }
        }

        // 3) Détection d'autres cas spéciaux ici (ex: quotes non fermées si tokens les signalent)

        prev = curr;
        curr = curr->next;
    }
    return 0;
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
	// if (!validate_syntax(tokens))
    // 	return NULL;
	ast = parse(&tokens);
	free_tokens(tokens);
	return (ast);
}
