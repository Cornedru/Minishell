int	check_quotes(char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[i] == '"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote); /* Return 1 if unmatched quotes */
}

char	*remove_quotes(char *str)
{
	char *result = malloc(ft_strlen(str) + 1);
	int i = 0, j = 0;
	int in_single = 0, in_double = 0;

	if (!result)
		return (NULL);

	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
		}
		else if (str[i] == '"' && !in_single)
		{
			in_double = !in_double;
		}
		else
		{
			result[j++] = str[i];
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}