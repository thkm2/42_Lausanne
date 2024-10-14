/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_number.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:33:58 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/11 12:39:43 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_unsigned_number(unsigned int nb, int *rs)
{
	if (nb > 9)
		ft_print_unsigned_number(nb / 10, rs);
	if (*rs == -1)
		return ;
	ft_print_char(nb % 10 + '0', rs);
}
