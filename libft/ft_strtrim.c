/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:49:12 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/02 19:37:25 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	int		h[256];
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ft_memset(h, 0, 256);
	while (set[i])
		h[set[i++] + 0] = 1;
	i = -1;
	while (s1[++i])
	{
		if (h[s1[i] + 0] != 1)
			j++;
	}
	ret = (char *)malloc(sizeof(char) * (j + 1));
	if (!ret)
		return (NULL);
	i += 1;
	while (--i >= 0)
	{
		if (h[s1[i] + 0] != 1)
			ret[j--] = s1[i];
	}
	return (ret);
}

/*#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 3)
		return(0);
	printf("%s \n", ft_strtrim(av[1], av[2]));
	return(0);
}*/