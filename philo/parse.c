/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:50:20 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/13 13:44:26 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_all_digit(char *s)
{
	while ((*s >= 9 && *s <= 13) || *s == 32
		|| *s == '+')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			s++;
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	nb;

	nb = 0;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	while (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		if (nb > (INT_MAX / 10 - *s - '0'))
			return_error("int max");
		nb *= 10;
		nb += *s - '0';
		s++;
	}
	return (nb);
}

int	input_is_valid(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!is_all_digit(av[i]))
			return (0);
		if (ft_atoi(av[i]) <= 0)
			return (0);
	}
	return (1);
}
