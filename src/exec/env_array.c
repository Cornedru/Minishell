/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:18:30 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/04 02:23:30 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**dup_array(char **array)
{
	int		i;
	int		count;
	char	**new;

	count = 0;
	while (array[count])
		count++;
	new = (char **)gc_malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (++i < count)
		new[i] = gc_strdup(array[i]);
	new[i] = NULL;
	return (new);
}

/**
 * env_getarray - make char **envp back from t_env *envp
 *
 * @envp: environment linked list
 * 
 * Return: envp array of strings.
 */
char	**env_getarray(t_env *envp)
{
	int		i;
	int		count;
	char	**array;

	count = ft_envsize(envp);
	array = (char **)gc_malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (++i < count)
	{
		if (!envp->content)
			array[i] = gc_strdup(envp->var);
		else
			array[i] = gc_strjoin_free_s1(gc_strjoin(envp->var, "="),
					envp->content);
		envp = envp->next;
	}
	array[i] = NULL;
	return (array);
}

int	update_env_array(t_sys *sys)
{
	gc_free_array((void **)sys->envp);
	sys->envp = env_getarray(sys->env_lst);
	if (!sys->envp)
		return (1);
	return (0);
}
