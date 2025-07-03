/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 07:49:49 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
