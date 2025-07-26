/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:40:52 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/27 00:42:19 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"
#include "stdio.h"

void	*gc_alloc(t_gc *gc, size_t size)
{
	void *ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_register(gc, ptr);
	fprintf(stderr, "🟢 Alloc %p (size %zu)\n", ptr, size); // 👈 log
	return (ptr);
}

void	*gc_alloc(t_gc *gc, size_t size)
{
	void *ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_register(gc, ptr);
	fprintf(stderr, "🟢 Alloc %p (size %zu)\n", ptr, size); // 👈 log
	return (ptr);
}

void	gc_bzero(void *s, size_t n)
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
