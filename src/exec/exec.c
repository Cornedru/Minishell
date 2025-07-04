/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:41:49 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/04 02:45:06 by oligrien         ###   ########.fr       */
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
	while (!sys->exit)
	{
		line = readline(PROMPT);
		if (!line)
			return (1);
		add_history(line);

		// Tokenize


		// Build AST
		/* ----------- MOCK AST ------------
		if (!ft_strcmp(line, "ls -l"))
			sys->ast = mock_ls_command();
		if (!ft_strcmp(line, "cat < input.txt"))
			sys->ast = mock_redir_in_command();
		if (!ft_strcmp(line, "ls -l | grep \".c\""))
			sys->ast = mock_pipe_command();
		if (!ft_strcmp(line, "export A=1 B=2 A=new C 1INVALID"))
			sys->ast = mock_export_command();
		if (!ft_strcmp(line, "export"))
			sys->ast = mock_export_no_args_command();
		if (!ft_strcmp(line, "unset A C NONEXISTENT"))
			sys->ast = mock_unset_command();
		if (!ft_strcmp(line, "cd /tmp"))
			sys->ast = mock_cd_command();
		if (!ft_strcmp(line, "env"))
			sys->ast = mock_env_command();
		if (!ft_strcmp(line, "exit f42"))
			sys->ast = mock_exit_command();
		if (!ft_strcmp(line, "echo \"testing redir\" > output.txt"))
			sys->ast = mock_redir_out_command();
		--------------------------------- */


		// Execute AST:
		if (sys->ast)
			sys->exit_status = execute(sys->ast, sys);
		gc_free(sys->ast);
	}
	return (0);
}
