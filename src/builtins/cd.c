/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:34:07 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*get_cd_path(char **argv, t_shell *shell)
{
	char	*path;
	char	*home;
	char	*oldpwd;

	if (!argv[1])
	{
		home = get_env_value("HOME", shell);
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
		path = home;
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		oldpwd = get_env_value("OLDPWD", shell);
		if (!oldpwd)
		{
			printf("cd: OLDPWD not set\n");
			return (NULL);
		}
		path = oldpwd;
		printf("%s\n", path);
	}
	else
		path = argv[1];
	return (path);
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
