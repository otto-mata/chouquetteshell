/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:50:10 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/16 17:18:02 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

void	ft_env(char **env)
{
	int i;

	i = 0;
	if(!env)
		return ;
	while(env[i] != 0)
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}

void	ft_unset(char **cmd, char **env)
{
	int			i;
	int			j;
	char 		**new_env;
	const int	size = ft_tablen(env) + 1;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return ;
	while (env[i])
	{
		if(is_in_tab(env[i], cmd) == 0)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
			{
				free_tab(new_env);
				return ;
			}
			j++;
		}
		i++;
	}
	new_env[i] = NULL;
	free_tab(env);
	dup_env(&env, new_env);
	free_tab(new_env);
	return ;
}
