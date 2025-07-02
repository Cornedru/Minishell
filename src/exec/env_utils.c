/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 02:30:33 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/02 20:33:50 by oligrien         ###   ########.fr       */
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

int	ft_envsize(t_env *envp)
{
	int	cnt;

	cnt = 0;
	while (envp)
	{
		cnt++;
		envp = envp->next;
	}
	return (cnt);
}

static t_env	*ft_envlast(t_env *envp)
{
	while (envp && envp->next)
		envp = envp->next;
	return (envp);
}

t_env	*gc_envnew(char *var, char *content)
{
	t_env	*node;

	node = (t_env *)gc_malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->var = var;
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_envadd_back(t_env **envp, t_env *new)
{
	t_env	*last;

	if (!envp || !new)
		return ;
	if (*envp == NULL)
		*envp = new;
	else
	{
		last = ft_envlast(*envp);
		last->next = new;
	}
}
