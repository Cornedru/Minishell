/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/03 06:41:05 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*alloc_token_node(char *value, t_token_type type)
{
	t_token	*tmp;

	tmp = gc_malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->type = type;
	tmp->value = gc_strdup(value);
	tmp->next = NULL;
	return (tmp);
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

t_token	*create_token_list(char **split_values, t_token_type type)
{
	t_token	*new_tokens;
	t_token	*tmp;
	int		i;

	new_tokens = NULL;
	i = 0;
	while (split_values[i])
	{
		if (ft_strlen(split_values[i]) == 0)
		{
			i++;
			continue ;
		}
		tmp = alloc_token_node(split_values[i], type);
		if (!tmp)
			break ;
		append_token(&new_tokens, tmp);
		i++;
	}
	return (new_tokens);
}

t_token	*split_expanded_token(char *expanded, t_token_type type)
{
	char	**split_values;
	t_token	*new_tokens;
	char	*clean;

	clean = normalize_whitespace(expanded);
	split_values = gc_split(clean, ' ');
	if (!split_values || !split_values[0])
	{
		if (split_values)
			gc_free_array((void **)split_values);
		return (NULL);
	}
	new_tokens = create_token_list(split_values, type);
	gc_free_array((void **)split_values);
	return (new_tokens);
}

void	process_quote(char *str, int *i, char **result, char quote)
{
	int		start;
	char	*segment_result;

	start = *i + 1;
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	segment_result = gc_substr(str, start, *i - start);
	*result = join_and_free(*result, segment_result);
	if (str[*i] == quote)
		(*i)++;
}
