/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:01:04 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/04 03:44:54 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_path(t_env *envp, char *arg)
{
	char	*path;

	if (!arg)
	{
		path = get_env_var("HOME", envp);
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set", 2);
			return (NULL);
		}
	}
	else if (!ft_strcmp(arg, "-"))
	{
		path = get_env_var("OLDPWD", envp);
		if (!path)
		{
			ft_putstr_fd("cd: OLDPWD not set", 2);
			return (NULL);
		}
	}
	else
		path = gc_strdup(arg);
	return (path);
}

static char	*ft_getcwd(char *buf, size_t size)
{
	char	*cwd;

	cwd = getcwd(buf, size);
	if (!cwd)
	{
		perror("cd: error retrieving current directory");
		return (NULL);
	}
	return (cwd);
}

int	builtin_cd(t_ast *node, t_sys *sys)
{
	char	*path;
	char	*cwd;
	
	cwd = ft_getcwd(NULL, 0);
	if (!cwd)
		return (perror("minishell: cd"), 1);
	path = get_path(sys->env_lst, node->args[1]);
	if (!path)
    	return (free(cwd), 1);
	if (!chdir(path))	// SUCCESS
	{
		if (set_env_var(sys, &sys->env_lst, "OLDPWD", cwd))
			return (free(cwd), gc_free(path), 1);
		free(cwd);
		cwd = ft_getcwd(NULL, 0);
		if (!cwd)
			return (perror("minishell: cd"), gc_free(path), 1);
		if (set_env_var(sys, &sys->env_lst, "PWD", cwd))
			return (free(cwd), gc_free(path), 1);
		return (free(cwd), gc_free(path), 0);
	}
	else				// FAILURE
		return (ft_putstr_fd("minishell: cd: ", 2), perror(path), free(cwd),
			gc_free(path), 1);
}

/* int	builtin_cd(t_ast *node, t_sys *sys)
{
	char	*path;
	char	*cwd;
	char	*nwd;
	
	cwd = getcwd(NULL, 0);
	if (!node->args[1])
	{
		path = get_env_var("HOME", sys->envp);
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set", 2);
			return (gc_free(cwd), 1);
		}
	}
	else if (!ft_strcmp(node->args[1], "-"))
	{
		path = get_env_var("OLDPWD", sys->envp);
		if (!path)
		{
			ft_putstr_fd("cd: OLDPWD not set", 2);
			return (gc_free(cwd), 1);
		}
	}
	else
		path = gc_strdup(node->args[1]);

	if (!chdir(path))
	{
		if (set_env_var(&sys->envp, "OLDPWD", cwd))
			return (gc_free(cwd), gc_free(path), 1);
		if (set_env_var(&sys->envp, "OLDPWD", getcwd(NULL, 0)))
			return (gc_free(cwd), gc_free(path), 1);
		return (gc_free(cwd), gc_free(path), 0);
	}
	else
	{
		perror("cd");
		return (gc_free(cwd), gc_free(path), 1);
	}
} */
