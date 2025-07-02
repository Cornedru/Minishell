/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:43:03 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/29 02:26:26 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	sub = NULL;
	if (start >= str_len)
		return (ft_free((void *)&sub), gc_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	sub = (char *)gc_malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (s && s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
