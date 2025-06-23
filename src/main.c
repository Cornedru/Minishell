/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:58:53 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_prompt(void)
// {
// 	printf("minishell$ ");
// 	fflush(stdout);
// }

// static int	execute_ast(t_ast *ast, t_shell *shell)
// {
// 	if (!ast)
// 		return (0);
// 	if (ast->type == AST_COMMAND)
// 		return (execute_command(ast, shell));
// 	else if (ast->type == AST_PIPELINE)
// 		return (execute_pipeline(ast, shell));
// 	else if (ast->type == AST_AND)
// 	{
// 		shell->last_status = execute_ast(ast->left, shell);
// 		if (shell->last_status == 0)
// 			return (execute_ast(ast->right, shell));
// 		return (shell->last_status);
// 	}
// 	else if (ast->type == AST_OR)
// 	{
// 		shell->last_status = execute_ast(ast->left, shell);
// 		if (shell->last_status != 0)
// 			return (execute_ast(ast->right, shell));
// 		return (shell->last_status);
// 	}
// 	else if (ast->type == AST_SUBSHELL)
// 		return (execute_ast(ast->left, shell));
// 	return (1);
// }