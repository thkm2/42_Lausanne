/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:22:08 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/05 09:35:56 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_how_many_substring(char const *s, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (in_substring == 0)
			{
				in_substring = 1;
				count++;
			}
		}
		else
			in_substring = 0;
		s++;
	}
	return (count);
}

int	ft_find_substring_index(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return (i);
		i++;
	}
	return (i);
}

void	ft_str_to_strs(char const *s, char c, char **tab, int substring_count)
{
	int	i;
	int	len;
	int	substring;

	i = 0;
	substring = 0;
	while (substring < substring_count)
	{
		len = 0;
		i += ft_find_substring_index(s + i, c);
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		tab[substring] = (char *)malloc(sizeof(char) * (len + 1));
		i -= len;
		len = 0;
		while (s[i] && s[i] != c)
			tab[substring][len++] = s[i++];
		tab[substring][len] = '\0';
		substring++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		substring_count;
	char	**tab;

	if (!s)
		return (NULL);
	substring_count = ft_how_many_substring(s, c);
	tab = (char **)malloc(sizeof(char *) * (substring_count + 1));
	if (!tab)
		return (NULL);
	tab[substring_count] = NULL;
	ft_str_to_strs(s, c, tab, substring_count);
	return (tab);
}

/*#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	char **tab = ft_split(av[1], av[2][0]);
	int i = 0;
	int count = ft_how_many_substring(av[1], av[2][0]);
	while (i < count)
		printf("%s \n", tab[i++]);
	return (0);
}*/