/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:47:06 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/05 23:13:21 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * builtin_echo
 *
 * @param node AST linked list
 * 
 * @return 0 = no error.
 */
int	builtin_echo(t_ast *node)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	while (is_n_option(node->args[i]))
	{
		n = 1;
		i++;
	}
	while (node->args[i])
	{
		ft_putstr_fd(node->args[i], 1);
		if (node->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}
