int	builtin_export(char **argv, t_shell *shell)
{
	int i = 1;
	char *key, *value;
	char *equals;

	if (!argv[1]) /* Print all exported variables */
	{
		print_exported_vars(shell);
		return (0);
	}

	while (argv[i])
	{
		equals = ft_strchr(argv[i], '=');
		if (equals)
		{
			*equals = '\0';
			key = argv[i];
			value = equals + 1;

			if (!is_valid_identifier(key))
			{
				printf("export: `%s': not a valid identifier\n", key);
				*equals = '='; /* Restore string */
				return (1);
			}

			set_env_value(key, value, shell);
			mark_as_exported(key, shell);
			*equals = '='; /* Restore string */
		}
		else
		{
			if (!is_valid_identifier(argv[i]))
			{
				printf("export: `%s': not a valid identifier\n", argv[i]);
				return (1);
			}
			mark_as_exported(argv[i], shell);
		}
		i++;
	}

	return (0);
}