/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: studio <studio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:35:22 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/26 15:44:48 by studio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
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
	printf("le résultat de mon isalpha : %d\n", ft_isalpha(c));
	printf("le résultat du vrai isalpha : %d\n", isalpha(c));
	printf("C est : %c\n", c);
	return (0);
}*/