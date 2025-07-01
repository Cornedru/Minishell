/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/01 23:43:43 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	mark_as_exported(char *key, t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			env->exported = 1;
			return ;
		}
		env = env->next;
	}
	set_env_value(key, "", shell);
	mark_as_exported(key, shell);
}

void	print_exported_vars(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->exported)
		{
			if (env->value)
				printf("declare -x %s=\"%s\"\n", env->key, env->value);
			else
				printf("declare -x %s\n", env->key);
		}
		env = env->next;
	}
}

// char	**env_to_array(t_env *env)
// {
// 	char	**envp;
// 	t_env	*current;
// 	int		count;
// 	int		i;
// 	char	*temp;

// 	count = 0;
// 	current = env;
// 	while (current)
// 	{
// 		if (current->value)
// 			count++;
// 		current = current->next;
// 	}
// 	envp = malloc(sizeof(char *) * (count + 1));
// 	if (!envp)
// 		return (NULL);
// 	i = 0;
// 	current = env;
// 	while (current && i < count)
// 	{
// 		if (current->value)
// 		{
// 			temp = ft_strjoin(current->key, "=");
// 			envp[i] = ft_strjoin(temp, current->value);
// 			free(temp);
// 			i++;
// 		}
// 		current = current->next;
// 	}
// 	envp[i] = NULL;
// 	return (envp);
// }

char	**env_to_array(t_env *env)
{
	char	**envp;
	t_env	*current;
	int		count;
	int		i;
	char	*temp;

	count = 0;
	current = env;
	// Count only exported variables with values
	while (current)
	{
		if (current->value && current->exported)
			count++;
		current = current->next;
	}
	
	// Always allocate at least 1 slot for NULL terminator
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
		
	i = 0;
	current = env;
	while (current && i < count)
	{
		if (current->value && current->exported)
		{
			temp = ft_strjoin(current->key, "=");
			if (!temp)
			{
				// Clean up on allocation failure
				while (--i >= 0)
					free(envp[i]);
				free(envp);
				return (NULL);
			}
			envp[i] = ft_strjoin(temp, current->value);
			free(temp);
			if (!envp[i])
			{
				// Clean up on allocation failure
				while (--i >= 0)
					free(envp[i]);
				free(envp);
				return (NULL);
			}
			i++;
		}
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}
