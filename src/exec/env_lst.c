/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:30:28 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/04 00:30:42 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envnode(t_env *env_lst)
{
	gc_free(env_lst->var);
	gc_free(env_lst->content);
	gc_free(env_lst);
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
