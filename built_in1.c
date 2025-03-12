/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:12:07 by seb               #+#    #+#             */
/*   Updated: 2025/03/12 19:25:06 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

typedef struct s_cmd
{
	char			**cmd;
	char			**limiter;
	char			*name_in;
	char			*name_out;
	int				fd_in;
	int				fd_out;
	int				append;
	int				state;
	struct s_cmd	*next;
}					t_cmd;

int	ft_pwd(void)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		perror("getcwd");
		return (0);
	}
	write(1, current_path, strlen(current_path));
	write(1, "\n", 1);
	free(current_path);
	return (1);
}

int	ft_cd(char **path, char **env)
{
	if (ft_tablen(path) == 1)
		path[1] = get_home(env);
	else if (ft_tablen(path) > 2)
		return (perror("too many arguments"), 0);
	change_old_pwd(env);
	if (chdir(path[1]) == -1)
		return (perror(path[1]), 0);
	change_pwd(env);
	return (1);
}

int	ft_echo(char **args, int newline)
{
	int	i;

	i = 1;
	if (!args)
		return (0);
	while (args[i])
	{
		write(1, args[i], strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	return (1);
}

static int	choice_of_builtin(char *line, char **env)
{
	if (ft_strncmp(line, "exit", 5) == 0)
		return (-1);
	else if (ft_strncmp(line, "cd", 3) == 0 || ft_strncmp(line, "cd", 3) == 32)
		ft_cd(ft_split(line, ' '), env);
	else if (ft_strncmp(line, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(line, "echo", 5) == 32)
		ft_echo(ft_split(line, ' '), 1);
	return (1);
}

void	here_doc_line(t_pipe pipe_fd, char **env)
{
	char	*line;
	int		i;
	int		result;

	(void)pipe_fd;
	i = 0;
	result = 1;
	while (result == 1)
	{
		line = readline("\e[32mMinishell : \e[0m");
		if (!line)
			return ;
		result = choice_of_builtin(line, env);
		free(line);
	}
}
