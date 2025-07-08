/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:43:55 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/05 23:19:46 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	env_print_sorted(t_env *env_lst)
{
	int		size;
	char	*last_printed;
	t_env	*candidate;
	t_env	*current;

	size = ft_envsize(env_lst);
	last_printed = NULL;
	while (size--)
	{
		candidate = NULL;
		current = env_lst;
		while (current)
		{
			if ((!last_printed || ft_strcmp(current->var, last_printed) > 0)
				&& (!candidate || ft_strcmp(current->var, candidate->var) < 0))
				candidate = current;
			current = current->next;
		}
		if (!candidate->content)
			printf("declare -x %s", candidate->var);
		else
			printf("declare -x %s=\"%s\"", candidate->var, candidate->content);
		last_printed = candidate->var;
	}
}

static void	parse_arg(char *arg, char **var, char **content)
{
	char	*equal_sign;
	
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*var = gc_substr(arg, 0, equal_sign - arg);
		*content = gc_strdup(equal_sign + 1);
	}
	else
	{
		*var = gc_strdup(arg);
		*content = NULL;
	}
}

static int	handle_arg(t_sys *sys, char *arg)
{
	char	*var;
	char	*content;
	int		error;

	parse_arg(arg, &var, &content);
	if (is_valid_identifier(var))
		error = set_env_var(sys, &sys->env_lst, var, content);
	else
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier", 2);
		error = 1;
	}
	gc_free(var);
	gc_free(content);
	return (error);
}

/**
 * builtin_export
 *
 * @param node AST linked list
 * @param sys system struct
 * 
 * @return 1 = error. 0 = no error.
 */
int	builtin_export(t_ast *node, t_sys *sys)
{
	int		error;
	int		i;

	error = 0;
	if (!node->args[1])
		return (env_print_sorted(sys->env_lst), 0);
	i = 0;
	while (node->args[++i])
	{
		if (handle_arg(sys, node->args[i]))
			error = 1;
	}
	if (error)
		return (1);
	return (0);
}
