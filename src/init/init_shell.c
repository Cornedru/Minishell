/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 00:55:48 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_shell_level(t_shell *shell)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env_value("SHLVL", shell);
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str);
		shlvl++;
	}
	else
		shlvl = 1;
	new_shlvl = ft_itoa(shlvl);
	set_env_value("SHLVL", new_shlvl, shell);
	free(new_shlvl);
}

static void	set_default_vars(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!get_env_value("PWD", shell) && pwd)
		set_env_value("PWD", pwd, shell);
	if (!get_env_value("OLDPWD", shell))
		set_env_value("OLDPWD", pwd, shell);
	free(pwd);
	set_shell_level(shell);
}

void	init_shell_environment(t_shell *shell)
{
	init_env(shell);
	set_default_vars(shell);
}