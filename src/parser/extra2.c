// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   extra2.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
// /*   Updated: 2025/07/06 06:15:32 by ndehmej          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// int	is_operator(char c)
// {
// 	return (c == '|' || c == '<' || c == '>' || c == '&');
// }

// int	skip_whitespace(char *input, int i)
// {
// 	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
// 		i++;
// 	return (i);
// }

// t_token_type	get_operator_type(char *input, int i)
// {
// 	if (input[i] == '|')
// 	{
// 		if (input[i + 1] == '|')
// 			return (TOKEN_OR);
// 		return (TOKEN_PIPE);
// 	}
// 	else if (input[i] == '<')
// 	{
// 		if (input[i + 1] == '<')
// 			return (TOKEN_HEREDOC);
// 		return (TOKEN_REDIR_IN);
// 	}
// 	else if (input[i] == '>')
// 	{
// 		if (input[i + 1] == '>')
// 			return (TOKEN_REDIR_APPEND);
// 		return (TOKEN_REDIR_OUT);
// 	}
// 	else if (input[i] == '&')
// 	{
// 		if (input[i + 1] == '&')
// 			return (TOKEN_AND);
// 		return (TOKEN_INVALID);
// 	}
// 	return (TOKEN_WORD);
// }

// int	are_quotes_closed(const char *str)
// {
// 	int	i;
// 	int	single;
// 	int	doubleq;

// 	i = 0;
// 	single = 0;
// 	doubleq = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && doubleq % 2 == 0)
// 			single++;
// 		else if (str[i] == '"' && single % 2 == 0)
// 			doubleq++;
// 		i++;
// 	}
// 	if (single % 2 == 0 && doubleq % 2 == 0)
// 		return (1);
// 	return (0);
// }

// char	*expand_variable(char *str, int *i, t_sys *sys)
// {
// 	char	*res;
// 	int		start;

// 	res = expand_special_var(str, i, sys);
// 	if (res)
// 		return (res);
// 	res = handle_invalid_or_numeric_var(str, i);
// 	if (res)
// 		return (res);
// 	start = *i + 1;
// 	return (extract_env_value(str, i, start, sys));
// }
// /* Ajouter dans extra2.c ou dans un nouveau fichier syntax.c */

// int	is_operator_token(t_token_type type)
// {
// 	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR);
// }

// //  int	check_redirection_syntax(t_token *curr)
// // {
// // 	if (!curr->next || curr->next->type != TOKEN_WORD)
// // 	{
// // 		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
// // 		if (!curr->next)
// // 			ft_putstr_fd("newline", 2);
// // 		else if (curr->next->type == TOKEN_PIPE)
// // 			ft_putstr_fd("|", 2);
// // 		else if (is_redirection_token(curr->next->type))
// // 			ft_putstr_fd(curr->next->value, 2);
// // 		ft_putstr_fd("'\n", 2);
// // 		return (0);
// // 	}
// // 	return (1);
// // }

// // int	check_operator_syntax(t_token *curr, t_token *prev)
// // {
// // 	if ((prev && is_operator_token(prev->type)) || !curr->next)
// // 	{
// // 		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
// // 		if (curr->type == TOKEN_PIPE)
// // 			ft_putstr_fd("|", 2);
// // 		else if (curr->type == TOKEN_AND)
// // 			ft_putstr_fd("&&", 2);
// // 		else if (curr->type == TOKEN_OR)
// // 			ft_putstr_fd("||", 2);
// // 		ft_putstr_fd("'\n", 2);
// // 		return (0);
// // 	}
// // 	return (1);
// // }

// int	validate_syntax(t_token *tokens)
// {
// 	t_token	*prev;
// 	t_token	*curr;

// 	prev = NULL;
// 	curr = tokens;
// 	if (curr && is_operator_token(curr->type))
// 		return (check_operator_syntax(curr, prev));
// 	while (curr)
// 	{
// 		if (is_redirection_token(curr->type))
// 		{
// 			if (!check_redirection_syntax(curr))
// 				return (0);
// 		}
// 		else if (is_operator_token(curr->type))
// 		{
// 			if (!check_operator_syntax(curr, prev))
// 				return (0);
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// 	return (1);
// }
// /* Ajouter ces fonctions dans extra2.c ou parser3.c */

// static int	count_args(char **args)
// {
// 	int	count;

// 	count = 0;
// 	if (!args)
// 		return (0);
// 	while (args[count])
// 		count++;
// 	return (count);
// }

// static char	**merge_args(char **old_args, char **new_args)
// {
// 	char	**result;
// 	int		old_count;
// 	int		new_count;
// 	int		i;
// 	int		j;

// 	old_count = count_args(old_args);
// 	new_count = count_args(new_args);
// 	result = (char **)gc_malloc(sizeof(char *) * (old_count + new_count + 1));
// 	if (!result)
// 		return (NULL);
// 	i = -1;
// 	while (++i < old_count)
// 		result[i] = old_args[i];
// 	j = -1;
// 	while (++j < new_count)
// 		result[i + j] = new_args[j];
// 	result[i + j] = NULL;
// 	gc_free(old_args);
// 	gc_free(new_args);
// 	return (result);
// }

// t_ast	*attach_redirections(t_ast *cmd, t_ast *redir)
// {
// 	t_ast	*temp;

// 	if (!redir)
// 		return (cmd);
// 	temp = redir;
// 	while (temp->left)
// 		temp = temp->left;
// 	temp->left = cmd;
// 	return (redir);
// }

// static int	handle_token_in_command(t_token **tokens, t_ast **cmd)
// {
// 	char	**additional_args;
// 	t_ast	*new_redir;

// 	if (is_redirection_token((*tokens)->type))
// 	{
// 		new_redir = parse_single_redirection(tokens);
// 		if (!new_redir)
// 			return (0);
// 		*cmd = attach_redirections(*cmd, new_redir);
// 	}
// 	else if ((*tokens)->type == TOKEN_WORD)
// 	{
// 		additional_args = gather_all_words(tokens);
// 		if (additional_args && additional_args[0])
// 		{
// 			(*cmd)->args = merge_args((*cmd)->args, additional_args);
// 			if (!(*cmd)->args)
// 				return (0);
// 		}
// 	}
// 	return (1);
// }

// int	parse_remaining_tokens(t_token **tokens, t_ast **cmd)
// {
// 	while (*tokens && (*tokens)->type != TOKEN_PIPE
// 		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
// 	{
// 		if (!handle_token_in_command(tokens, cmd))
// 			return (0);
// 		if (*tokens && (*tokens)->type != TOKEN_WORD 
// 			&& !is_redirection_token((*tokens)->type))
// 			break ;
// 	}
// 	return (1);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/06 06:15:32 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	skip_whitespace(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

t_token_type	get_operator_type(char *input, int i)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			return (TOKEN_OR);
		return (TOKEN_PIPE);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (TOKEN_REDIR_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	else if (input[i] == '&')
	{
		if (input[i + 1] == '&')
			return (TOKEN_AND);
		return (TOKEN_INVALID);
	}
	return (TOKEN_WORD);
}

int	are_quotes_closed(const char *str)
{
	int	i;
	int	single;
	int	doubleq;

	i = 0;
	single = 0;
	doubleq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && doubleq % 2 == 0)
			single++;
		else if (str[i] == '"' && single % 2 == 0)
			doubleq++;
		i++;
	}
	if (single % 2 == 0 && doubleq % 2 == 0)
		return (1);
	return (0);
}

char	*expand_variable(char *str, int *i, t_sys *sys)
{
	char	*res;
	int		start;

	res = expand_special_var(str, i, sys);
	if (res)
		return (res);
	res = handle_invalid_or_numeric_var(str, i);
	if (res)
		return (res);
	start = *i + 1;
	return (extract_env_value(str, i, start, sys));
}

int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = tokens;
	if (curr && is_operator_token(curr->type))
		return (check_operator_syntax(curr, prev));
	while (curr)
	{
		if (is_redirection_token(curr->type))
		{
			if (!check_redirection_syntax(curr))
				return (0);
		}
		else if (is_operator_token(curr->type))
		{
			if (!check_operator_syntax(curr, prev))
				return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}

static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

char	**merge_args(char **old_args, char **new_args)
{
	char	**result;
	int		old_count;
	int		new_count;
	int		i;
	int		j;

	old_count = count_args(old_args);
	new_count = count_args(new_args);
	result = (char **)gc_malloc(sizeof(char *) * (old_count + new_count + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < old_count)
		result[i] = old_args[i];
	j = -1;
	while (++j < new_count)
		result[i + j] = new_args[j];
	result[i + j] = NULL;
	gc_free(old_args);
	gc_free(new_args);
	return (result);
}

t_ast	*attach_redirections(t_ast *cmd, t_ast *redir)
{
	t_ast	*temp;

	if (!redir)
		return (cmd);
	temp = redir;
	while (temp->left)
		temp = temp->left;
	temp->left = cmd;
	return (redir);
}

static int	handle_token_in_command(t_token **tokens, t_ast **cmd)
{
	char	**additional_args;
	t_ast	*new_redir;

	if (is_redirection_token((*tokens)->type))
	{
		new_redir = parse_single_redirection(tokens);
		if (!new_redir)
			return (0);
		*cmd = attach_redirections(*cmd, new_redir);
	}
	else if ((*tokens)->type == TOKEN_WORD)
	{
		additional_args = gather_all_words(tokens);
		if (additional_args && additional_args[0])
		{
			(*cmd)->args = merge_args((*cmd)->args, additional_args);
			if (!(*cmd)->args)
				return (0);
		}
	}
	return (1);
}

int	parse_remaining_tokens(t_token **tokens, t_ast **cmd)
{
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if (!handle_token_in_command(tokens, cmd))
			return (0);
		if (*tokens && (*tokens)->type != TOKEN_WORD 
			&& !is_redirection_token((*tokens)->type))
			break ;
	}
	return (1);
}