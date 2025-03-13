/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:37:51 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/13 13:05:46 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static int	dup_env(char ***env, char **envp)
{
	int			i;
	const int	size = ft_tablen(envp) + 1;

	i = 0;
	if (!envp)
		return (-1);
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

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipe_fd;
	t_cmd	cmd;
	char	**env;

	(void)argc;
	(void)argv;
	cmd.cmd = NULL;
	if (dup_env(&env, envp) == -1)
		return (0);
	if (pipe(pipe_fd.old) == -1)
	{
		free_tab(env);
		return (0);
	}
	write(1, "\033[H\033[J", 6);
	here_doc_line(cmd, pipe_fd, env);
	free_tab(env);
	close(pipe_fd.old[0]);
	close(pipe_fd.old[1]);
	return (0);
}
