/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/07/02 00:12:47 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quoted_segment(char *str, int *i, t_shell *shell, char **result)
{
	char	quote;

	quote = str[*i];
	if (quote == '\'')
		handle_single_quote(str, i, result);
	else
		handle_double_quote(str, i, shell, result);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}
