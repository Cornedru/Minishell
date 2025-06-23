/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:37:38 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/23 22:48:04 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

int	testoverflow(int x, int y)
{
	return (x * y);
}

static void	test_basic_types(void)
{
	int		a;
	char	*str;
	char	*str2;
	char	*str3;

	a = 42;
	str = "Hello World!";
	str2 = "";
	str3 = NULL;
	printf(">>> ON TESTE c (ft_printf puis printf)\n\n");
	ft_printf("Bonjour %c\n", 'e');
	printf("Bonjour %c\n", 'e');
	printf(">>> ON TESTE s (ft_printf puis printf)\n\n");
	ft_printf("Je dis : %s\n", str);
	printf("Je dis : %s\n", str);
	ft_printf("Bonjour (str vide) : %s\n", str2);
	printf("Bonjour (str vide) : %s\n", str2);
}

int	main(void)
{
	test_basic_types();
	return (0);
}
