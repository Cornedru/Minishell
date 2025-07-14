/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/06 06:19:28 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int	check_redirection_syntax(t_token *curr)
{
	// printf("coucou");
	if (!curr->next || curr->next->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!curr->next)
			ft_putstr_fd("newline", 2);
		else if (curr->next->type == TOKEN_PIPE)
			ft_putstr_fd("|", 2);
		else if (is_redirection_token(curr->next->type))
			ft_putstr_fd(curr->next->value, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

int	check_operator_syntax(t_token *curr, t_token *prev)
{
	if ((prev && is_operator_token(prev->type)) || !curr->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (curr->type == TOKEN_PIPE)
			ft_putstr_fd("|", 2);
		else if (curr->type == TOKEN_AND)
			ft_putstr_fd("&&", 2);
		else if (curr->type == TOKEN_OR)
			ft_putstr_fd("||", 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

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