/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:26:17 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/11 11:55:43 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_char(char c, int *rs)
{
	int	success;

	success = write(1, &c, 1);
	(*rs)++;
	if (success == -1)
		*rs = -1;
}
