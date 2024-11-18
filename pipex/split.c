/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:58:39 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/12 17:33:19 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_count_words(char const *s, char c)
{
	int	nb_w;
	int	in_words;

	nb_w = 0;
	in_words = 0;
	while (*s)
	{
		if (*s != c && in_words == 0)
		{
			in_words = 1;
			nb_w++;
		}
		else if (*s == c)
			in_words = 0;
		s++;
	}
	return (nb_w);
}

int	ft_count_char(char const *s, char c)
{
	int	nb_c;

	nb_c = 0;
	while (*s && *s == c)
		s++;
	while (*s && *s != c)
	{
		nb_c++;
		s++;
	}
	return (nb_c);
}

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	ft_star_to_stars(char **tab, char const *s, char c, int nb_w)
{
	int	word;
	int	i;

	word = 0;
	while (word < nb_w)
	{
		while (*s && *s == c)
			s++;
		tab[word] = (char *)malloc(sizeof(char) * (ft_count_char(s, c) + 1));
		if (!tab[word])
		{
			ft_free_split(tab);
			return (0);
		}
		i = 0;
		while (*s && *s != c)
		{
			tab[word][i++] = *s;
			s++;
		}
		tab[word][i] = '\0';
		word++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nb_w;

	if (!s)
		return (NULL);
	nb_w = ft_count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_w + 1));
	if (!tab)
		return (NULL);
	if (!ft_star_to_stars(tab, s, c, nb_w))
		return (NULL);
	tab[nb_w] = NULL;
	return (tab);
}
