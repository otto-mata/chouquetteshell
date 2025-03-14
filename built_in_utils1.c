/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:28:59 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/14 13:05:47 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	change_pwd(char **env, char *path)
{
	char	*new_pwd;
	int		i;

	i = 0;
	while (env[i])
	{
		if (strncmp("PWD=", env[i], 4) == 0)
			break ;
		i++;
	}
	if (path[0] != '/')
		path = create_new_path(env, path);
	new_pwd = ft_strjoin("PWD=", path);
	if (!new_pwd)
		return (perror("ft_strjoin"));
	free(env[i]);
	free(path);
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
	cwd = ft_getenv("PWD=", env);
	if (!cwd)
		return (perror("ft_getenv"));
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (!old_pwd)
		return (perror("ft_strjoin"));
	free(env[i]);
	free(cwd);
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
	if (!env[i])
		return (0);
	return (env[i] + 5);
}

int	check_flags(t_cmd cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (!cmd.cmd[1])
		return (1);
	while (cmd.cmd[i][0] == '-' && cmd.cmd[i][j] == 'n')
	{
		if (cmd.cmd[i][j] != 'n')
			break ;
		j++;
		if (!cmd.cmd[i][j])
		{
			i++;
			j = 1;
		}
	}
	return (i);
}

char	*ft_getenv(char *value_name, char **env)
{
	int			i;
	char		*value_env;
	const int	size_value_name = ft_strlen(value_name);

	i = 0;
	while (env[i])
	{
		if (strncmp(value_name, env[i], size_value_name) == 0)
			break ;
		i++;
	}
	value_env = ft_strdup(env[i] + size_value_name);
	return (value_env);
}
