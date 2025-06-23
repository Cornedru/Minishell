/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:48:36 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	handle_export_with_value(char *arg, t_shell *shell)
{
	char	*equals;
	char	*key;
	char	*value;

	equals = ft_strchr(arg, '=');
	*equals = '\0';
	key = arg;
	value = equals + 1;
	if (!is_valid_identifier(key))
	{
		printf("export: `%s': not a valid identifier\n", key);
		*equals = '=';
		return (1);
	}
	set_env_value(key, value, shell);
	mark_as_exported(key, shell);
	*equals = '=';
	return (0);
}

static int	handle_export_no_value(char *arg, t_shell *shell)
{
	if (!is_valid_identifier(arg))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	mark_as_exported(arg, shell);
	return (0);
}

static int	process_export_args(char **argv, t_shell *shell)
{
	int		i;
	char	*equals;

	i = 1;
	while (argv[i])
	{
		equals = ft_strchr(argv[i], '=');
		if (equals)
		{
			if (handle_export_with_value(argv[i], shell) != 0)
				return (1);
		}
		else
		{
			if (handle_export_no_value(argv[i], shell) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_export(char **argv, t_shell *shell)
{
	if (!argv[1])
	{
		print_exported_vars(shell);
		return (0);
	}
	return (process_export_args(argv, shell));
}
