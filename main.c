/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:37:51 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/14 13:06:29 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static int	dup_env(char ***env, char **envp)
{
	int			i;
	const int	size = ft_tablen(envp) + 1;

	i = 0;
	*env = malloc(sizeof(char *) * size);
	if (!*env)
		return (-1);
	while (envp[i])
	{
		(*env)[i] = ft_strdup(envp[i]);
		if (!(*env)[i])
		{
			free_tab(*env);
			return (-1);
		}
		i++;
	}
	(*env)[i] = NULL;
	return (1);
}

int	create_env(char ***env)
{
	*env = malloc(sizeof(char *) * 3);
	(*env)[0] = ft_strjoin(ft_strdup("PWD="), getcwd(NULL, 0));
	if (!(*env)[0])
		return (-1);
	(*env)[1] = ft_strdup("OLDPWD=");
	if (!(*env)[1])
		return (free((*env)[0]), free(*env), -1);
	(*env)[3] = 0;
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipe_fd;
	t_cmd	cmd;
	char	**env;
	long	result;

	(void)argc;
	(void)argv;
	cmd.cmd = NULL;
	if (!envp[0])
		create_env(&env);
	else if (dup_env(&env, envp) == -1)
		return (0);
	if (pipe(pipe_fd.old) == -1)
	{
		free_tab(env);
		return (0);
	}
	write(1, "\033[H\033[J", 6);
	result = here_doc_line(cmd, pipe_fd, env);
	free_tab(env);
	close(pipe_fd.old[0]);
	close(pipe_fd.old[1]);
	return (0);
}
