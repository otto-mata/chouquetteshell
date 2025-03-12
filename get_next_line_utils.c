/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:29:21 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/11 13:35:19 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*zone;

	if (size != 0 && nmemb > (size_t) - 1 / size)
		return (0);
	zone = (void *) malloc(nmemb * size);
	if (!zone)
		return (0);
	ft_bzero(zone, size * nmemb);
	return (zone);
}
