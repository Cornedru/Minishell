/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/03 02:50:24 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[i] == '"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

void	copy_quoted_content(char *str, int *i, int *j, char *result)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		result[(*j)++] = str[*i];
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
}

int	count_quoted_chars(char *str, int *i)
{
	char	quote;
	int		len;

	quote = str[*i];
	(*i)++;
	len = 0;
	while (str[*i] && str[*i] != quote)
	{
		len++;
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
	return (len);
}

int	get_unquoted_length(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			len += count_quoted_chars(str, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = (char *)gc_malloc(get_unquoted_length(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			copy_quoted_content(str, &i, &j, result);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
