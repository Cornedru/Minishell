#include <stdlib.h>
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count = 0;
	int	in_word = 0;

	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*alloc_word(const char *start, size_t len)
{
	char	*word = malloc(len + 1);
	size_t	i = 0;

	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_all(char **res, int i)
{
	while (--i >= 0)
		free(res[i]);
	free(res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i = 0;
	size_t	len;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len)
		{
			res[i] = alloc_word(s, len);
			if (!res[i++])
				return (free_all(res, i), NULL);
			s += len;
		}
	}
	res[i] = NULL;
	return (res);
}
