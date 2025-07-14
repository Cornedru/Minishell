/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:54:16 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/15 01:20:11 by ndehmej          ###   ########.fr       */
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

/**
 * find_cmd_path - Find command path
 * 
 * @param sys system struct
 * @param cmd command name
 * 
 * @return 1 = error. 0 = no error.
 */
char	*find_cmd_path(t_sys *sys, char *cmd)
{
	char	**env_paths;
	char	*cmd_path;
	char	*tmp;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))	// if cmd is already a path
	{
		if (access(cmd, X_OK) == 0)
			return (gc_strdup(cmd));
		return (NULL);
	}
	tmp = get_env_var("PATH", sys->env_lst);
	if (!tmp)
		return (NULL);
	env_paths = gc_split(tmp, ':');
	cmd_path = pull_path(env_paths, cmd);
	gc_free_array((void **)env_paths);
	return (cmd_path);
}
