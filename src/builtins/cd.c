int	builtin_cd(char **argv, t_shell *shell)
{
	char *path;
	char *home;
	char *oldpwd;

	if (!argv[1]) /* cd with no arguments */
	{
		home = get_env_value("HOME", shell);
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		path = home;
	}
	else if (ft_strcmp(argv[1], "-") == 0) /* cd - */
	{
		oldpwd = get_env_value("OLDPWD", shell);
		if (!oldpwd)
		{
			printf("cd: OLDPWD not set\n");
			return (1);
		}
		path = oldpwd;
		printf("%s\n", path);
	}
	else
		path = argv[1];

	/* Save current directory as OLDPWD */
	set_env_value("OLDPWD", shell->cwd, shell);

	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}

	/* Update PWD */
	free(shell->cwd);
	shell->cwd = getcwd(NULL, 0);
	set_env_value("PWD", shell->cwd, shell);

	return (0);
}