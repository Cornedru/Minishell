/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 00:41:14 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands(t_ast *node)
{
	if (node->type != AST_PIPELINE)
		return (1);
	return (count_commands(node->left) + count_commands(node->right));
}

static void	setup_pipes(int **pipes, int cmd_index, int total_cmds)
{
	if (cmd_index > 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < total_cmds - 1)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
}

static void	close_all_pipes(int **pipes, int total_cmds)
{
	int	i;

	i = 0;
	while (i < total_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	execute_pipeline_child(t_ast *node, int **pipes,
				int cmd_index, int total_cmds)
{
	char	*cmd_path;
	char	**envp;

	setup_child_signals();
	setup_pipes(pipes, cmd_index, total_cmds);
	close_all_pipes(pipes, total_cmds);
	if (setup_redirections(node->redirs) == -1)
		exit(1);
	if (is_builtin(node->argv[0]))
		exit(execute_builtin(node, shell));
	cmd_path = find_command_path(node->argv[0], shell);
	envp = env_to_array(shell->env);
	if (!cmd_path)
		exit(127);
	execve(cmd_path, node->argv, envp);
	exit(127);
}
