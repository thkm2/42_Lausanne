/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: studio <studio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:04:35 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/26 15:50:36 by studio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	int c = atoi(av[1]);
	printf("le résultat de mon isdigit : %d\n", ft_isdigit(c));
	printf("le résultat du vrai isdigit : %d\n", isdigit(c));
	printf("C est : %c\n", c);
	return (0);
}*/