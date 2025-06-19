/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 02:22:41 by ndehmej           #+#    #+#             */
/*   Updated: 2024/10/29 05:53:42 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	j;
	int	i;
	int	m;

	j = 0;
	i = 0;
	m = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m = m * -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		j = j * 10 + (str[i] - '0');
		i++;
	}
	return (j * m);
}
/*
#include<stdio.h>
int	main()
{
	char	str[] = "  ----+--+123 4ab567";
	printf("%i", ft_atoi(str));
}
*/
