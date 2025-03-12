/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:28:59 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/12 19:24:50 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	change_pwd(char **env)
{
	char	*cwd;
	char	*new_pwd;
	int		i;

	i = 0;
	while (env[i])
	{
		if (strncmp("PWD=", env[i], 4) == 0)
			break ;
		i++;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("getcwd"));
	new_pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!new_pwd)
		return (perror("ft_strjoin"));
	free(env[i]);
	env[i] = new_pwd;
}

void	change_old_pwd(char **env)
{
	char	*cwd;
	char	*old_pwd;
	int		i;

	i = 0;
	while (env[i])
	{
		if (strncmp("OLDPWD=", env[i], 7) == 0)
			break ;
		i++;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("getcwd"));
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	if (!old_pwd)
		return (perror("ft_strjoin"));
	free(env[i]);
	env[i] = old_pwd;
}

char	*get_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp("HOME=", env[i], 5) == 0)
			break ;
		i++;
	}
	return (env[i] + 5);
}
