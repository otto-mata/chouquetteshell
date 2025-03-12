/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:03:48 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/11 14:20:33 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Minishell_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_args
{
	char	*file;
	char	*full_path;
	char	**executable;
}			t_args;

typedef struct s_here_doc
{
	char	**cmd1;
	char	**cmd2;
	char	*limiter;
	char	*file;
	int		state;
}			t_here_doc;

typedef struct s_pipe
{
	int		old[2];
	int		new[2];
}			t_pipe;

// Minishell_built_in.c
int main(int argc, char **argv, char **envp);
///////////////////////////////////////////////////////////////////////////////

// mini_libft.c
int			ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlcpy(char *dst, const char *src, int size);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
///////////////////////////////////////////////////////////////////////////////

//get_next_line
char	*get_lines(char *buffer, char *init_line);
void	next_line(char *buffer);
char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_bzero(void *s, size_t n);
///////////////////////////////////////////////////////////////////////////////

// ft_split.c
char		**ft_split(char const *s, char c);
char		**ft_split1(char const *s, char c);
////////////////////////////////////////////////////////
#endif