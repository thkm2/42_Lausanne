/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:16:08 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/11 12:39:49 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_number(int n, int *rs)
{
	long	nb;

	nb = (long)n;
	if (n < 0)
	{
		ft_print_char('-', rs);
		nb = (long)-nb;
	}
	if (nb > 9)
		ft_print_number(nb / 10, rs);
	if (*rs == -1)
		return ;
	ft_print_char(nb % 10 + '0', rs);
}
