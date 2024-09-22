/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_isalnum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:37:26 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/22 19:38:10 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int	ft_isalnum(int c);

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	int c = atoi(av[1]);
	printf("le résultat de mon isalpha : %d\n", ft_isalnum(c));
	printf("le résultat du vrai isalpha : %d\n", isalnum(c));
	printf("C est : %c\n", c);
	return (0);
}
