/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:54:16 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 06:22:59 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*pull_path(char **env_paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = -1;
	while (env_paths && env_paths[++i])
	{
		tmp = gc_strjoin(env_paths[i], "/");
		cmd_path = gc_strjoin(tmp, cmd);
		gc_free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		gc_free(cmd_path);
	}
	return (NULL);
}

char	*find_cmd_path(t_sys *sys, char *cmd)
{
	char	**env_paths;
	char	*path_var;
	char	*cmd_path;

	// Handle absolute or relative paths directly
	if (cmd && (cmd[0] == '/' || cmd[0] == '.'))
	{
		if (access(cmd, X_OK) == 0)
			return (gc_strdup(cmd));
		return (NULL);
	}

	// Get PATH from environment
	path_var = get_env_var("PATH", sys->env_lst);
	if (!path_var)
		return (NULL);

	env_paths = gc_split(path_var, ':');
	if (!env_paths)
		return (NULL);

	cmd_path = pull_path(env_paths, cmd);
	gc_free_array((void **)env_paths);

	return (cmd_path);
}
