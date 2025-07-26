/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:09:10 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/27 00:36:02 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <stdio.h>

#include "../includes/gc.h"

char	*gc_strdup(const char *s)
{
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	dup = (char *)gc_malloc(i + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}



