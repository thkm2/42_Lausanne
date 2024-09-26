/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: studio <studio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:13:14 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/26 15:52:56 by studio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;
	size_t				i;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	i = 0;
	while (source[i] && i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}

/*#include <stdio.h>
#include <string.h>

int main(void)
{
	char dst[] = "123456";
	char src[] = "456";
	size_t n = 3;
	ft_memcpy(dst, src, n);
	printf("ma fonction : %s \n", dst);

	char dst2[] = "123456";
	char src2[] = "456";
	memcpy(dst2, src2, n);
	printf("la vrai fonction : %s \n", dst2);
	return (0);
}*/