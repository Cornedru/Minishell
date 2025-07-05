/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:03:37 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/05 23:31:26 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	open_redirect_file(char *filename, t_ast_type type)
{
	int	fd;

	fd = -1;
	if (type == AST_REDIR_IN || type == AST_HEREDOC)
		fd = open(filename, O_RDONLY);
	else if (type == AST_REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == AST_REDIR_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(filename);
	}
	return (fd);
}

/**
 * handle_redirection - Fd management for redirections
 *
 * @param node ast node containing command name
 * @param sys system structure
 *
 * @return Exit code from recursive execute call.
 */
int	handle_redirection(t_ast *node, t_sys *sys)
{
	int	file_fd;
	int	original_fd;
	int	target_fd;
	int	status;

	file_fd = open_redirect_file(node->filename, node->type);
	if (file_fd == -1)
		return (1); // Return error status
	if (node->type == AST_REDIR_IN || node->type == AST_HEREDOC)
		target_fd = STDIN_FILENO;
	else
		target_fd = STDOUT_FILENO;
	original_fd = dup(target_fd);
	if (dup2(file_fd, target_fd) == -1)
	{
		perror("minishell: dup2");
		close(file_fd);
		return (1);
	}
	close(file_fd); // The FD is now duplicated, we can close the original
	status = execute(node->left, sys);
	dup2(original_fd, target_fd); // Restore the original stdin/stdout
	close(original_fd);
	return (status);
}
