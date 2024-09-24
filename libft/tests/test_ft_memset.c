/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:11:53 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/24 14:47:46 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len);

int main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	size_t len = atoi(av[2]);
	unsigned char *b = malloc(sizeof(unsigned char) * (len));
	int c = atoi(av[1]);
	ft_memset(b, c, len);
	size_t i = 0;
	while (i < len)
		printf("%c", b[i++]);
	printf("\n");
	i = 0;
	memset(b, 0, len);
	memset(b, c, len);
	while (i < len)
		printf("%c", b[i++]);
	return (0);
}
