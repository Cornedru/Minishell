/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:41:49 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 06:26:03 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute(t_ast *node, t_sys *sys)
{
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (handle_pipe(node, sys));
	else if (node->type == AST_CMD)
		return (execute_cmd(node, sys));
	else if (node->type >= AST_REDIR_IN && node->type <= AST_HEREDOC)
		return (handle_redirection(node, sys));
	return (1);
}
