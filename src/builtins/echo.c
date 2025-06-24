/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 05:00:51 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;
	int	first_word;

	i = 1;
	newline = 1;
	first_word = 1;
	
	// Parse all -n flags (bash behavior: multiple -n flags are allowed)
	while (argv[i] && is_valid_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	
	// Print arguments
	while (argv[i])
	{
		if (!first_word)
			printf(" ");
		printf("%s", argv[i]);
		first_word = 0;
		i++;
	}
	
	if (newline)
		printf("\n");
	
	return (0);
}