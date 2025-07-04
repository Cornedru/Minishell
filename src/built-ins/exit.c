/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:59:51 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/04 04:22:42 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if(++i > 19)
			return (0);
	}
	if (ft_strcmp(str, "9223372036854775807") > 0)
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
		sys->exit_status = ft_atoi(node->args[1]) % 256;
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
