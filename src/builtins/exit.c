/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/28 00:14:33 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	
	if (!str[i])
		return (0);
		
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
		
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	
	return (result * sign);
}

static int	is_overflow(char *str)
{
	int		len;
	int		i;
	int		sign;
	
	if (!str || !*str)
		return (1);
	
	i = 0;
	sign = 1;
	
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	
	while (str[i] == '0')
		i++;
	
	len = 0;
	while (str[i + len] && ft_isdigit(str[i + len]))
		len++;
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (sign == 1)
	{
		if (ft_strncmp(&str[i], "9223372036854775807", 19) > 0)
			return (1);
	}
	else
	{
		if (ft_strncmp(&str[i], "9223372036854775808", 19) > 0)
			return (1);
	}
	return (0);
}

static int	check_numeric_overflow(char *str)
{
	if (!is_valid_number(str))
		return (1);
	
	return (is_overflow(str));
}

// char *realloc(char *s, int new, int old)
// {
// 	int i = 0;
// 	char *res;
	
// 	if (!s)
// 		return (NULL);
// 	res = malloc(sizeof(char) * new);
// 	if (!res)
// 		return (NULL);
// 	while (i >= old && s[i])
// 	{
// 		res[i] = s[i];
// 		i++;
// 	}
// 	free(s);
// 	return (res);
// }

int	builtin_exit(char **argv, t_shell *shell)
{
	int		exit_code;
	int		argc;

	exit_code = shell->last_status;
	
	argc = 0;
	while (argv[argc])
		argc++;

	if (shell->interactive)
		ft_putstr_fd("exit\n", 1);
	
	if (argc == 1)
	{
		cleanup_shell(shell);
		exit(exit_code);
	}
	if (argc == 2)
	{
		if (check_numeric_overflow(argv[1]) || !is_valid_number(argv[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			cleanup_shell(shell);
			exit(2);
		}
		exit_code = (unsigned char)ft_atoll(argv[1]);
		cleanup_shell(shell);
		exit(exit_code);
	}
	// argc > 2
	if (check_numeric_overflow(argv[1]) || !is_valid_number(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		cleanup_shell(shell);
		exit(2);
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}