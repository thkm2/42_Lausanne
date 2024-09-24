/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:08:58 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/24 14:28:28 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	unsigned char *p;

	i = 0;
	p = (unsigned char *)b;
	while (i < len)
		p[i++] = (unsigned char)c;
	return (p);
}
