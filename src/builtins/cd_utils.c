/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:51:44 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_path(char **argv, t_shell *shell)
{
	if (!argv[1])
		return (get_home_path(shell));
	else if (ft_strcmp(argv[1], "-") == 0)
		return (get_oldpwd_path(shell));
	else
		return (argv[1]);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*path;

	path = get_cd_path(argv, shell);
	if (!path)
		return (1);
	set_env_value("OLDPWD", shell->cwd, shell);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	free(shell->cwd);
	shell->cwd = getcwd(NULL, 0);
	set_env_value("PWD", shell->cwd, shell);
	return (0);
}
