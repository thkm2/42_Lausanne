/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:50:03 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/01 20:04:58 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac != 4)
		return (0);
	printf("ma fonction : %d \n", ft_strncmp(av[1], av[2], (size_t)atoi(av[3])));
	printf("la vraie : %d \n", strncmp(av[1], av[2], (size_t)atoi(av[3])));
	return (0);
}*/