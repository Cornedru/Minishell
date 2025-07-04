/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:33:06 by oligrien          #+#    #+#             */
/*   Updated: 2025/07/04 04:07:54 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return ("");
	else if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)ft_calloc(len + 1, sizeof(char));
	if (!join)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		join[i + j] = s2[j];
	return (join);
}

char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (ft_free((void *)&s1), "");
	else if (!s1)
		return (ft_free((void *)&s1), (char *)s2);
	else if (!s2)
		return (ft_free((void *)&s1), (char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)ft_calloc(len + 1, sizeof(char));
	if (!join)
		return (ft_free((void *)&s1), NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		join[i + j] = s2[j];
	return (ft_free((void *)&s1), join);
}

char	*ft_strjoin_free_s2(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (ft_free((void *)&s2), "");
	else if (!s1)
		return (ft_free((void *)&s2), (char *)s2);
	else if (!s2)
		return (ft_free((void *)&s2), (char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)ft_calloc(len + 1, sizeof(char));
	if (!join)
		return (ft_free((void *)&s2), NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		join[i + j] = s2[j];
	return (ft_free((void *)&s2), join);
}

char	*ft_strjoin_free_s1_s2(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (ft_free((void *)&s1), ft_free((void *)&s2), "");
	else if (!s1)
		return (ft_free((void *)&s1), ft_free((void *)&s2), (char *)s2);
	else if (!s2)
		return (ft_free((void *)&s1), ft_free((void *)&s2), (char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)ft_calloc(len + 1, sizeof(char));
	if (!join)
		return (ft_free((void *)&s1), ft_free((void *)&s2), NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		join[i + j] = s2[j];
	return (ft_free((void *)&s1), ft_free((void *)&s2), join);
}
