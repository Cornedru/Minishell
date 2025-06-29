/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:31:47 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/26 23:34:44 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

static int	wordcnt(char const *s, char c)
{
	int	cnt;
	int	i;

	if (!s)
		return (0);
	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
			cnt++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (cnt);
}

static size_t	wordlen(char const *s, char c)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**gc_split(char const *s, char c)
{
	char	**split;
	int		wcnt;
	int		i;

	wcnt = wordcnt(s, c);
	if (!wcnt)
		return (NULL);
	split = (char **)gc_malloc(sizeof(char *) * (wcnt + 1));
	if (!split)
		return (NULL);
	i = -1;
	while (++i < wcnt)
	{
		while (s && (char)(*s) == c)
			s++;
		if (s)
		{
			split[i] = ft_substr(s, 0, wordlen(s, c));
			if (!split[i])
				return (ft_free_strarr((void ***)&split), NULL);
			s += wordlen(s, c) + 1;
		}
	}
	split[i] = NULL;
	return (split);
}
