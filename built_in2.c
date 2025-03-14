/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:50:10 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/14 13:33:15 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


long ft_atol(const char *str) {
    long result = 0;
    int sign = 1;
	
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\v' || *str == '\f')
	{
        str++;
    }
    if (*str == '-')
	{
        sign = -1;
        str++;
    } else if (*str == '+')
	{
        str++;
    }
    while (*str >= '0' && *str <= '9')
	{
        result = result * 10 + (*str - '0');
        str++;
    }
	result = result * sign;
	printf("%ld\n", result);
	if (result < 0)
		return (-1);
    return (result);
}

long	ft_exit(char **cmd)
{
	unsigned int	result;

	(void)cmd;
	result = ft_atol(cmd[1]);
	
	return (result);
}
