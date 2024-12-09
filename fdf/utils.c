/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:18:33 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/02 16:38:29 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	return_error(char *s, t_fdf *env)
{
	ft_free_fdf(env);
	perror(s);
	exit(1);
}

int	ft_atoi_hex(const char *s)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'x'))
		i += 2;
	while ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f')
		|| (s[i] >= 'A' && s[i] <= 'F'))
	{
		nb *= 16;
		if (s[i] >= 'a' && s[i] <= 'f')
			nb += s[i] - 87;
		else if (s[i] >= 'A' && s[i] <= 'F')
			nb += s[i] - 55;
		else if (s[i] >= '0' && s[i] <= '9')
			nb += s[i] - '0';
		i++;
	}
	return (nb);
}

int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}
