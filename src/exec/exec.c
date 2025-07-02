/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:41:49 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/02 23:18:42 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_line(t_sys *sys)
{
	char	*line;

	line = NULL;
	while (!(sys->exit))
	{
		line = readline("MiniShell> ");
		if (!line)
			return (0);
		if (ft_strlen(line) > 0)
		{
			add_history(line);

			// Tokenize

			// Build AST
			// ----------- MOCK AST ------------
			// sys->ast = mock_ls_command();
			// sys->ast = mock_redir_command();
			sys->ast = mock_pipe_command();
			// ---------------------------------

			// Execute AST:
			if (sys->ast)
				sys->exit_status = execute(sys->ast, sys);
			gc_free(sys->ast);
		}
		else
			printf("(empty line)\n");
	}
	return (1);
}
