/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:36:50 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/11 12:22:40 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_string(char *s, int *rs)
{
	if (!s)
	{
		ft_print_string("(null)", rs);
		return ;
	}
	while (*s)
	{
		if (*rs == -1)
			return ;
		ft_print_char(*s, rs);
		s++;
	}
}
