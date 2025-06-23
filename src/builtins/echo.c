int	builtin_echo(char **argv)
{
	int i = 1;
	int newline = 1;

	/* Check for -n flag */
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}

	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");

	return (0);
}