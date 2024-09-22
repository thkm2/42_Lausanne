/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isdigit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:16:07 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/22 15:16:45 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int	ft_isdigit(int c);

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	int c = atoi(av[1]);
	printf("le résultat de mon isalpha : %d\n", ft_isdigit(c));
	printf("le résultat du vrai isalpha : %d\n", isdigit(c));
	printf("C est : %c\n", c);
	return (0);
}
