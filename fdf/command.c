/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:37:41 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/03 13:13:49 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_print_commands(t_fdf *env)
{
	mlx_string_put(env->mlx, env->win, 10, 10, 0xFFFFFF,
		"Zoom : fleche haut/bas");
	mlx_string_put(env->mlx, env->win, 10, 40, 0xFFFFFF,
		"Rotation : fleche gauche/droite");
	mlx_string_put(env->mlx, env->win, 10, 70, 0xFFFFFF,
		"Z : command/option de droite");
	mlx_string_put(env->mlx, env->win, 10, 100, 0xFFFFFF, "Shift : W/A/S/D");
	mlx_string_put(env->mlx, env->win, 10, 130, 0xFFFFFF, "Couleur : 1/2/3/4");
	mlx_string_put(env->mlx, env->win, 10, 160, 0xFFFFFF, "Quitter : esc");
}

int	ft_close_window(t_fdf *env)
{
	ft_free_fdf(env);
	exit(0);
	return (0);
}

void	ft_shift(int key, t_fdf *env)
{
	if (key == 13)
		env->camera->add_shift_y -= 10;
	else if (key == 0)
		env->camera->add_shift_x -= 10;
	else if (key == 1)
		env->camera->add_shift_y += 10;
	else if (key == 2)
		env->camera->add_shift_x += 10;
}

void	ft_change_color(int key, t_fdf *env)
{
	if (key == 21)
		env->map->def_color = 0xFFFFFF;
	else if (key == 19)
		env->map->def_color = 0xFF0000;
	else if (key == 20)
		env->map->def_color = 0x00FF83;
	else if (key == 18)
		env->map->def_color = 0x0000FF;
}
