/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:25:56 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/03 13:17:02 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf	*env;

	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./fdf <map.fdf>", 2);
		return (1);
	}
	env = ft_env_init(av[1]);
	ft_parse_map(av[1], env);
	ft_hook(env);
	ft_draw(env);
	ft_print_commands(env);
	mlx_loop(env->mlx);
	ft_free_fdf(env);
	return (0);
}
