/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:22:13 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/21 14:22:53 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_find_nl(char *s)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (NULL);
}

char	*ft_strcat_in_memory(char *memory, char *s1, char *s2, int len)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (s1)
	{
		while (s1[++i])
			memory[i] = s1[i];
	}
	else
		i = 0;
	while (s2[++j] && j < len)
		memory[i + j] = s2[j];
	memory[i + j] = '\0';
	return (memory);
}

char	*ft_find_line(char *s)
{
	int		len;
	char	*tmp;
	char	*line;

	if (!s || !*s)
		return (NULL);
	tmp = ft_find_nl(s);
	if (tmp)
		len = tmp - s + 1;
	else
		len = ft_strlen_gnl(s);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line = ft_strcat_in_memory(line, NULL, s, len);
	return (line);
}

char	*ft_find_rest(char *s)
{
	int		len;
	char	*start;
	char	*rest;

	if (!s)
		return (NULL);
	start = ft_find_nl(s);
	if (!start)
	{
		free(s);
		return (NULL);
	}
	start += 1;
	len = ft_strlen_gnl(start);
	rest = (char *)malloc(sizeof(char) * (len + 1));
	if (!rest)
	{
		free(s);
		return (NULL);
	}
	rest = ft_strcat_in_memory(rest, NULL, start, len);
	free(s);
	return (rest);
}
