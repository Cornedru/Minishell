/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:51:58 by ndehmej           #+#    #+#             */
/*   Updated: 2024/10/18 19:16:28 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*str;
	unsigned char		v;
	size_t				i;

	v = (unsigned char)c;
	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = v;
		i++;
	}
	return (b);
}
/*
#include <stdio.h>

int main() {
    char str[8] = "Bonjour"; 
    printf("%s\n", str);

    ft_memset(str, '0', 7);
    
    printf("%s\n", str);
    return (0);
}
*/
