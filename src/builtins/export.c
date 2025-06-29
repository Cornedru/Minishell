/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/28 00:08:19 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("=", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
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
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	
	// In bash, export VAR without value just marks it as exported
	// but doesn't create the variable if it doesn't exist
	t_env *env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, arg) == 0)
		{
			env->exported = 1;
			return (0);
		}
		env = env->next;
	}
	
	// Variable doesn't exist, create it without value but mark as exported
	set_env_value(arg, NULL, shell);
	mark_as_exported(arg, shell);
	return (0);
}

static void	sort_env_array(char **env_array, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_array[j], env_array[j + 1]) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_exported_vars_sorted(t_shell *shell)
{
	t_env	*env;
	char	**env_array;
	int		count;
	int		i;
	char	*equals;
	
	count = 0;
	env = shell->env;
	while (env)
	{
		if (env->exported)
			count++;
		env = env->next;
	}
	
	if (count == 0)
		return;
	env_array = malloc(sizeof(char *) * count);
	if (!env_array)
		return;
	i = 0;
	env = shell->env;
	while (env && i < count)
	{
		if (env->exported)
		{
			if (env->value)
			{
				char *temp = ft_strjoin(env->key, "=");
				env_array[i] = ft_strjoin(temp, env->value);
				free(temp);
			}
			else
				env_array[i] = ft_strdup(env->key);
			i++;
		}
		env = env->next;
	}
	sort_env_array(env_array, count);
	i = 0;
	while (i < count)
	{
		equals = ft_strchr(env_array[i], '=');
		if (equals)
		{
			*equals = '\0';
			printf("declare -x %s=\"%s\"\n", env_array[i], equals + 1);
		}
		else
		{
			printf("declare -x %s\n", env_array[i]);
		}
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

static int	process_export_args(char **argv, t_shell *shell)
{
	int		i;
	char	*equals;
	int		error_count;

	i = 1;
	error_count = 0;
	while (argv[i])
	{
		equals = ft_strchr(argv[i], '=');
		if (equals)
		{
			if (handle_export_with_value(argv[i], shell) != 0)
				error_count++;
		}
		else
		{
			if (handle_export_no_value(argv[i], shell) != 0)
				error_count++;
		}
		i++;
	}
	return (error_count > 0 ? 1 : 0);
}

int	builtin_export(char **argv, t_shell *shell)
{
	if (!argv[1])
	{
		print_exported_vars_sorted(shell);
		return (0);
	}
	return (process_export_args(argv, shell));
}