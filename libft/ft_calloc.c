/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:46:04 by ndehmej           #+#    #+#             */
/*   Updated: 2024/11/05 10:14:28 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdint.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*temp;

	if (nmemb == 0 || size == 0)
	{
		temp = malloc(0);
		return (temp);
	}
	if (nmemb * size / size != nmemb)
		return (NULL);
	temp = malloc(nmemb * size);
	if (temp == NULL)
		return (NULL);
	ft_bzero(temp, nmemb * size);
	return (temp);
}
