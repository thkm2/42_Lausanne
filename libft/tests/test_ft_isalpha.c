/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_isalpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:35:29 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/22 14:51:23 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int	ft_isalpha(int c);

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	int c = atoi(av[1]);
	printf("le résultat de mon isalpha : %d\n", ft_isalpha(c));
	printf("le résultat du vrai isalpha : %d\n", isalpha(c));
	printf("C est : %c\n", c);
	return (0);
}
