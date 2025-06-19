/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:32:00 by ndehmej           #+#    #+#             */
/*   Updated: 2024/10/18 19:19:53 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>

void ft_bzero(void *s, size_t n);

int main(void)
{
    char str[] = "Bonjour, comment tu vas";
    
    printf("%s\n", str);

    ft_bzero(str + 7, 5); 

    printf("%s\n", str);
    
    return 0;
}
*/
