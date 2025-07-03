/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:41:49 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 01:04:11 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute(t_ast *node, t_sys *sys)
{
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (handle_pipe(node, sys));
	else if (node->type >= AST_REDIR_IN && node->type <= AST_HEREDOC)
		return (handle_redirection(node, sys));
	else if (node->type == AST_CMD)
		return (execute_cmd(node, sys));
	// else if AND/OR
	return (1);
}

int	read_line(t_sys *sys)
{
	char	*line;

	line = NULL;
	while (!(sys->exit))
	{
		line = readline(PROMPT);
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
