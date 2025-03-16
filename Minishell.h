/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:03:48 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/16 15:18:58 by sle-nogu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_args
{
	char			*file;
	char			*full_path;
	char			**executable;
}					t_args;

typedef struct s_cmd
{
	char			**cmd;
	char			**limiter;
	char			*name_in;
	char			*name_out;
	int				fd_in;
	int				fd_out;
	int				append;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipe
{
	int				old[2];
	int				new[2];
}					t_pipe;

// built_in1.c
int					ft_pwd(char **env);
int					ft_cd(char **path, char **envp);
int					ft_echo(t_cmd cmd);
int					here_doc_line(t_cmd cmd, t_pipe pipe_fd, char **envp);
///////////////////////////////////////////////////////////////////////////////

// built_in2.c
void				ft_exit(char **cmd);
void				ft_env(char **env);
void				ft_unset(char **cmd, char **env);
int					is_in_tab(char *str, char **cmd);
///////////////////////////////////////////////////////////////////////////////

// mini_libft.c
int					ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strlcpy(char *dst, const char *src, int size);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
///////////////////////////////////////////////////////////////////////////////

// ft_split.c
char				**ft_split(char const *s, char c);
char				**ft_split1(char const *s, char c);
////////////////////////////////////////////////////////

// main.c
int					main(int argc, char **argv, char **envp);
int					dup_env(char ***env, char **envp);
///////////////////////////////////////////////////////////////////////////////

// tablen.c
int					ft_tablen(char **tab);
///////////////////////////////////////////////////////////////////////////////

// clear.c
void				free_tab(char **tab);
///////////////////////////////////////////////////////////////////////////////

// built_in_utils1.c
void				change_pwd(char **env, char *path);
void				change_old_pwd(char **env);
char				*get_home(char **env);
int					check_flags(t_cmd cmd);
char				*ft_getenv(char *value_name, char **env);
///////////////////////////////////////////////////////////////////////////////

// built_in_utils2.c
char				*create_new_path(char **env, char *path);
long				ft_atol(const char *str, long *result);
///////////////////////////////////////////////////////////////////////////////

#endif