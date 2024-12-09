/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:25:54 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/29 18:45:17 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_map(t_map *map)
{
	int	y;

	if (!map)
		return ;
	y = -1;
	while (++y < map->height)
		free(map->points[y]);
	free(map->points);
	free(map);
}

void	ft_free_fdf(t_fdf *env)
{
	if (!env)
		return ;
	if (env->map)
		ft_free_map(env->map);
	if (env->camera)
		free(env->camera);
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->mlx && env->win)
		mlx_destroy_window(env->mlx, env->win);
	free(env);
}
