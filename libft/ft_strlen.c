/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: studio <studio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:07:27 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/26 15:56:54 by studio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	const char *s = av[1];
	printf("ma fonction : %zu\n", ft_strlen(s));
	printf("la vraie : %zu\n", ft_strlen(s));
	return (0);
}*/