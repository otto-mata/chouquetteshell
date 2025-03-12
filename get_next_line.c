/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:24:49 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/11 13:41:36 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	write_line(char *line, char *buffer, int size, int i)
{
	int	j;

	j = 0;
	while (j < size)
		line[i++] = buffer[j++];
	if (buffer[j] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
}

char	*get_lines(char *buffer, char *init_line)
{
	int		size;
	char	*line;
	int		i;
	int		j;

	size = 0;
	i = 0;
	j = 0;
	while (buffer[size] != '\n' && buffer[size] != 0)
		size++;
	line = ft_calloc(sizeof(char), ft_strlen(init_line) + size + 2);
	if (!line)
	{
		free(init_line);
		return (0);
	}
	while (init_line[i] != 0)
		line[i++] = init_line[j++];
	j = 0;
	write_line(line, buffer, size, i);
	free(init_line);
	return (line);
}

void	next_line(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i] != '\0')
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}

char	*read_and_fill_line(int fd, char *line, char *buffer)
{
	int	nb_read;

	while (!ft_strlen(line) || line[ft_strlen(line) - 1] != '\n')
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read <= 0)
		{
			if (nb_read == 0 && ft_strlen(line) > 0)
				return (line);
			free(line);
			return (NULL);
		}
		buffer[nb_read] = 0;
		line = get_lines(buffer, line);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = ft_calloc(1, 1);
	if (!line)
		return (NULL);
	if (buffer[0] != 0)
	{
		next_line(buffer);
		line = get_lines(buffer, line);
		if (!line)
			return (NULL);
	}
	return (read_and_fill_line(fd, line, buffer));
}
