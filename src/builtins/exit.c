/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:52:11 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **argv, t_shell *shell)
{
	int	exit_code;

	exit_code = shell->last_status;
	printf("exit\n");
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
		{
			printf("exit: %s: numeric argument required\n", argv[1]);
			exit_code = 2;
		}
		else if (argv[2])
		{
			printf("exit: too many arguments\n");
			return (1);
		}
		else
		{
			exit_code = ft_atoi(argv[1]);
		}
	}
	cleanup_shell(shell);
	exit(exit_code);
}
