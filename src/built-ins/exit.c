/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:59:51 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/04 06:14:50 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_num(char *str)
{
	long long int	nb;
	int				fail;

	fail = 0;
	nb = ft_atoll(str , &fail);
	if (fail > 0)
		return (0);
	return (1);
}

int	builtin_exit(t_ast *node, t_sys *sys)
{
	ft_putstr_fd("exit\n", 1);
	if (!node->args[1])
	{
		sys->exit = 1;
		return (0);
	}
	if (is_valid_num(node->args[1]))
	{
		if (node->args[2])
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
				1);
		sys->exit = 1;
		sys->exit_status = ft_atoll(node->args[1], NULL) % 256;
	}
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		sys->exit = 1;
		sys->exit_status = 255;
	}
	return (sys->exit_status);
}
