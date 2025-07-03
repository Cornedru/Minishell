/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:34:42 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 01:01:43 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char const **argv, char **envp)
{
	t_sys	*sys;

	(void)argc;
	(void)argv;

	sys = init_sys(envp);

	read_line(sys);

	gc_free_array((void **)sys->envp);
	gc_destroy();
	return (0);
}
