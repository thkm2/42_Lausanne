/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:18:27 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/22 13:17:17 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **rs_line);

int		ft_strlen_gnl(char *s);
char	*ft_find_nl(char *s);
char	*ft_strcat_in_memory(char *memory, char *s1, char *s2, int len);
char	*ft_strjoin_gnl(char *rest, char *buffer);
char	*ft_find_line(char *s);
char	*ft_find_rest(char *s);

#endif