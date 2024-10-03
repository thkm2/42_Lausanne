/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:49:12 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/03 10:21:39 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_real_lenght(char s1, int *h)
{
	if (h[s1 + 0] != 1)
		return (1);
	return (0);
}

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
		j += ft_real_lenght(s1[i], h);
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