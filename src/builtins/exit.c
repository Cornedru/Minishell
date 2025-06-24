/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/06/24 05:03:09 by ndehmej          ###   ########.fr       */
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
	
	// Skip whitespace
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	
	// Check sign
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	
	// Skip leading zeros
	while (str[i] == '0')
		i++;
	
	// Count remaining digits
	len = 0;
	while (str[i + len] && ft_isdigit(str[i + len]))
		len++;
	
	// More than 19 digits is definitely overflow
	if (len > 19)
		return (1);
	
	// Less than 19 digits is definitely OK
	if (len < 19)
		return (0);
	
	// Exactly 19 digits - check against limits
	if (sign == 1)
	{
		// Compare with "9223372036854775807"
		if (ft_strncmp(&str[i], "9223372036854775807", 19) > 0)
			return (1);
	}
	else
	{
		// Compare with "9223372036854775808" (absolute value of LLONG_MIN)
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

int	builtin_exit(char **argv, t_shell *shell)
{
	int		exit_code;
	int		argc;

	exit_code = shell->last_status;
	
	argc = 0;
	while (argv[argc])
		argc++;

	if (shell->interactive)
		printf("exit\n");
	if (argc == 1)
	{
		cleanup_shell(shell);
		exit(exit_code);
	}
	if (argc == 2)
	{
		if (check_numeric_overflow(argv[1]) || !is_valid_number(argv[1]))
		{
			printf("bash: exit: %s: numeric argument required\n", argv[1]);
			cleanup_shell(shell);
			exit(2);
		}
		exit_code = (unsigned char)ft_atoll(argv[1]);
		cleanup_shell(shell);
		exit(exit_code);
	}
	if (check_numeric_overflow(argv[1]) || !is_valid_number(argv[1]))
	{
		printf("bash: exit: %s: numeric argument required\n", argv[1]);
		cleanup_shell(shell);
		exit(2);
	}
	printf("bash: exit: too many arguments\n");
	return (1);
}