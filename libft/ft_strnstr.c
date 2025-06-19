/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 02:05:38 by ndehmej           #+#    #+#             */
/*   Updated: 2024/10/29 05:07:29 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	compare;
	char	*big1;

	i = 0;
	big1 = (char *)big;
	compare = 1;
	if (!big && len == 0)
		return (NULL);
	if (*little == '\0')
		return (big1);
	while (big1[i] && i < len)
	{
		if ((big1[i] == *little) && (i + ft_strlen(little) <= len))
			compare = ft_memcmp(&big1[i], little, ft_strlen(little));
		if (compare == 0)
			return (&big1[i]);
		i++;
	}
	return (0);
}
