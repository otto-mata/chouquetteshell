/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell_built_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:12:07 by seb               #+#    #+#             */
/*   Updated: 2025/03/11 14:21:30 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <termios.h>
#include <sys/ioctl.h>
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
}			t_cmd;


int ft_pwd()
{
    char    *current_path;

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

int ft_cd(char *path, char **envp)
{
	char **env;
    char *new_pwd;
    char *cwd;
    int i = 0;

	env = envp;
    if (!path)
        return (0);
    if (chdir(path) == -1)
    {
        perror(path);
        return (0);
    }
    // Chercher et remplacer la variable PWD dans envp
    while (env[i])
    {
        if (strncmp("PWD=", env[i], 4) == 0)
            break;
        i++;
    }
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd");
        return (0);
    }
    new_pwd = ft_strjoin("PWD=", cwd);
    free(cwd);
    if (!new_pwd)
    {
        perror("ft_strjoin");
        return (0);
    }
    env[i] = new_pwd;
    return (1);
}

int ft_echo(char **args, int newline)
{
    int i;

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
    return (1);
}


static void	here_doc_line(t_pipe pipe_fd, char **envp)
{
	char	*line;
    int     i;
    

    (void)pipe_fd;
    i = 0;
	while (1)
	{
        write(1, "\e[32mMinishell : \e[0m", 21);
		write(1, getcwd(NULL, 0), ft_strlen(getcwd(NULL, 0)));
        write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return ;
        while(line[i])
        {
            if(line[i] == '\n')
            {
                line[i] = 0;
                break;
            }
            i++;
        }
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			return ;
		}
		else if(ft_strncmp(line, "cd", 2) == 0)
            ft_cd(line + 3 , envp);
        else if(ft_strncmp(line, "pwd", 3) == 0)
            ft_pwd();
        else if(ft_strncmp(line, "echo", 4) == 0)
            ft_echo(ft_split(line, ' '), 1);
		free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	// t_cmd cmd;
	t_pipe pipe_fd;
    (void)argc;
    (void)argv;
    (void)envp;
	if(pipe(pipe_fd.old) == -1)
		return (0);
	here_doc_line(pipe_fd, envp);
    close(pipe_fd.old[0]);
    close(pipe_fd.old[1]);
    return 0;
}
