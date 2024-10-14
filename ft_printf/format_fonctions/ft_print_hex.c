/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:40:15 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/11 12:39:35 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_hex(unsigned int nb, char *base, int *rs)
{
	if (nb > 15)
		ft_print_hex(nb / 16, base, rs);
	if (*rs == -1)
		return ;
	ft_print_char(base[nb % 16], rs);
}
