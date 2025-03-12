/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:11:31 by sle-nogu          #+#    #+#             */
/*   Updated: 2025/03/11 14:20:47 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	detect;

	i = 0;
	detect = 0;
	while (*str)
	{
		if (*str != c && detect == 0)
		{
			detect = 1;
			i++;
		}
		else if (*str == c)
			detect = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (0);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	split_string(const char *s, char c, char **tab)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			tab[j++] = word_dup(s, start, i);
			start = -1;
		}
		i++;
	}
	tab[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	
	if (!s || !c)
		return (NULL);
	if (s[0] == 32 && s[1] == 0)
	{
		tab = malloc(sizeof(char *) * 1);
		if(!tab)
			return (0);
		tab[0] = 0;
		return (tab);
	}
	tab = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		exit (EXIT_FAILURE);
	split_string(s, c, tab);
	return (tab);
}
