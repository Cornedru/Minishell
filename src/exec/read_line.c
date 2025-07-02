/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:22:08 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/10 00:35:58 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* static int	check_unmatched_quotes(const char *line)
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
} */


/* char	*read_line(void)
{
	char	*line;

	line = NULL;
	line = readline("MiniShell> ");
	if (!line)
		return (NULL);
	if (ft_strlen(line) > 0)
		add_history(line);
	else
		printf("(empty line)\n");
	return (line);
} */
