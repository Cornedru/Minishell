/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 00:38:16 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/05 23:19:40 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * builtin_env
 *
 * @param sys system struct
 * 
 * @return 0 = no error.
 */
int	builtin_env(t_sys *sys)
{
	t_env *current;

	// if (node->args[1])
	// {
	// 	ft_putstr_fd("env: ", 2);
	// 	ft_putstr_fd(node->args[1], 2);
	// 	ft_putstr_fd(": No such file or directory\n", 2);
	// 	return (127);
	// }
	current = sys->env_lst;
	while (current)
	{
		if (current->content)
			printf("%s=%s\n", current->var, current->content);
		current = current->next;
	}
	return (0);
}
