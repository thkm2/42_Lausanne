/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_bzero.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:02:22 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/24 15:22:34 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_bzero(void *s, size_t n);

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	size_t n = atoi(av[1]);
	unsigned char *s = malloc(sizeof(unsigned char) * (n));
	ft_bzero(s, n);
	size_t i = 0;
	while (i < n)
		printf("%hhu", s[i++]);
	printf("\n");
	i = 0;
	bzero(s, n);
	bzero(s, n);
	while (i < n)
		printf("%hhu", s[i++]);
	return (0);
}
