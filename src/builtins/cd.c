/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:52:08 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(t_shell *shell)
{
	char	*home;

	home = get_env_value("HOME", shell);
	if (!home)
	{
		printf("cd: HOME not set\n");
		return (NULL);
	}
	return (home);
}

static char	*get_oldpwd_path(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", shell);
	if (!oldpwd)
	{
		printf("cd: OLDPWD not set\n");
		return (NULL);
	}
	printf("%s\n", oldpwd);
	return (oldpwd);
}
