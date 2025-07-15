/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/15 02:50:20 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
