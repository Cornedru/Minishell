/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 05:04:12 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_tokens(t_token *tokens)
// {
// 	t_token	*tmp;

// 	while (tokens)
// 	{
// 		tmp = tokens->next;
// 		free(tokens->value);
// 		free(tokens);
// 		tokens = tmp;
// 	}
// }

// void	free_redirs(t_redir *redirs)
// {
// 	t_redir	*tmp;

// 	while (redirs)
// 	{
// 		tmp = redirs->next;
// 		free(redirs->file);
// 		free(redirs);
// 		redirs = tmp;
// 	}
// }

// void	free_ast(t_ast *ast)
// {
// 	if (!ast)
// 		return ;
// 	if (ast->argv)
// 		ft_free_split(ast->argv);
// 	if (ast->redirs)
// 		free_redirs(ast->redirs);
// 	free_ast(ast->left);
// 	free_ast(ast->right);
// 	free(ast);
// }

// void	free_env(t_env *env)
// {
// 	t_env	*tmp;

// 	while (env)
// 	{
// 		tmp = env->next;
// 		free(env->key);
// 		free(env->value);
// 		free(env);
// 		env = tmp;
// 	}
// }

// void	cleanup_shell(t_shell *shell)
// {
// 	free_env(shell->env);
// 	free(shell->cwd);
// }