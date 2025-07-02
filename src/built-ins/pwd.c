/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 03:03:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/29 03:09:19 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(void)
{
	char	*wd;
	
	wd = getcwd(NULL, 0);
	if (!wd)
	{
		perror("pwd");
		ft_free((void *)&wd);
		return (1);
	}
	ft_putstr_fd(wd, 1);
	ft_putchar_fd('\n', 1);
	ft_free((void *)&wd);
	return (0);
}
