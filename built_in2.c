/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:50:10 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/15 17:57:57 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

long	convert_string_to_long(const char *str, long *result, int sign)
{
	long	check_overflow;

	check_overflow = 0;
	*result = 0;
	while (*str >= '0' && *str <= '9')
	{
		*result = *result * 10 + (*str - '0');
		if (*result < check_overflow)
			return (-1);
		check_overflow = *result;
		str++;
	}
	*result *= sign;
	return (1);
}

long	ft_atol(const char *str, long *result)
{
	int	sign;

	sign = 1;
	*result = 0;
	if (!str)
		return (1);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (convert_string_to_long(str, result, sign) == -1)
		return (-1);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str != '\0')
	{
		*result = 2;
		return (-1);
	}
	return (1);
}

void	ft_exit(char **cmd)
{
	int				result;
	long			exit_value;
	unsigned int	test;

	(void)cmd;
	result = ft_atol(cmd[1], &exit_value);
	test = exit_value;
	if (result == 1)
	{
		if (!cmd[1])
			exit(test);
		else if (!cmd[2])
			exit(test);
		else if (cmd[2] != 0)
			write(1, "too many arguments\n", 19);
	}
	else if (result == -1)
	{
		write(1, "only numeric argument\n", 22);
		exit(test);
	}
}
