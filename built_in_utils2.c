/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:44:33 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/14 11:56:14 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*create_new_path(char **env, char *path)
{
	char	*cwd;
	char	*temp;

	cwd = ft_getenv("PWD=", env);
	if (!cwd)
		return (perror("ft_getenv"), NULL);
	temp = ft_strjoin(cwd, "/");
	if (!temp)
		return (free(cwd), perror("ft_strjoin"), NULL);
	free(cwd);
	cwd = ft_strjoin(temp, path);
	if (!cwd)
		return (free(temp), free(path), perror("ft_strjoin"), NULL);
	free(path);
	free(temp);
	path = ft_strdup(cwd);
	if (!path)
		return (free(cwd), perror("ft_strdup"), NULL);
	free(cwd);
	return (path);
}
