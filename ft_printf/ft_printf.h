/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:08:00 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/10 13:34:48 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);

void	ft_print_char(char c, int *rs);
void	ft_print_string(char *s, int *rs);
void	ft_print_ptr(void *ptr, char *base, int *rs);
void	ft_print_number(int n, int *rs);
void	ft_print_unsigned_number(unsigned int nb, int *rs);
void	ft_print_hex(unsigned int nb, char *base, int *rs);

#endif