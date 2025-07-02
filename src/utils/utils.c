/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/02 21:46:49 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// void	free_env(t_env *env)
// {
// 	t_env	*tmp;

// 	while (env)
// 	{
// 		tmp = env->next;
// 		free(env->key);
// 		free(env->value);
// 		free(env);
// 		env = tmp;
// 	}
// }

// void	cleanup_shell(t_shell *shell)
// {
// 	free_env(shell->env);
// 	free(shell->cwd);
// }

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}