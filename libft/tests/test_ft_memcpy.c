/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memcpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:37:23 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/25 12:29:58 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

int main(void)
{
	char dst[] = "123456";
	char src[] = "456";
	size_t n = 3;
	ft_memcpy(dst, src, n);
	printf("%s \n", dst);

	char dst2[] = "123456";
	char src2[] = "456";
	memcpy(dst2, src2, n);
	printf("%s \n", dst2);
	return (0);
}
