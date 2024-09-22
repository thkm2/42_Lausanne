/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:30:04 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/22 20:44:42 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strlen(const char *s);

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	const char *s = av[1];
	printf("ma fonction : %d\n", ft_strlen(s));
	printf("la vraie : %d\n", ft_strlen(s));
	return (0);
}
