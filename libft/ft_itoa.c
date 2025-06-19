#include <stdlib.h>
#include "libft.h"

static int	num_len(int n)
{
	int	len = (n <= 0);

	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len = num_len(n);
	long	nb = n;

	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		res[0] = '0';
	while (nb)
	{
		res[len--] = '0' + (nb % 10);
		nb /= 10;
	}
	return (res);
}
