/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:07:20 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/03 13:13:05 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_transform(t_fdf *env, int *x, int *y, int z)
{
	int	scale;
	int	old_x;
	int	old_y;

	scale = env->camera->zoom;
	*x *= scale;
	*y *= scale;
	z *= scale * env->camera->z_height;
	*x -= (env->map->width * scale) / 2;
	*y -= (env->map->height * scale) / 2;
	old_x = *x;
	old_y = *y;
	*x = (old_x - old_y) * cos(env->camera->angle);
	*y = (old_x + old_y) * sin(env->camera->angle) - z;
	*x += WIDTH / 2 + env->camera->add_shift_x;
	*y += HEIGHT / 2 + env->camera->add_shift_y;
}

void	ft_put_pixel_to_image(t_fdf *env, int x, int y, int color)
{
	int		position;
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	position = (y * env->size_line) + (x * (env->bpp / 8));
	dst = env->addr + position;
	if (color == -1)
		color = env->map->def_color;
	*(unsigned int *)dst = color;
}

int	ft_find_direction(int n_1, int n_2)
{
	if (n_1 > n_2)
		return (-1);
	return (1);
}

void	ft_draw_line(t_fdf *env, int *pos, int color)
{
	t_bresenham	b;

	ft_transform(env, &pos[0], &pos[1], env->map->points[pos[1]][pos[0]].z);
	ft_transform(env, &pos[2], &pos[3], env->map->points[pos[3]][pos[2]].z);
	b.x_distance = ft_abs(pos[0] - pos[2]);
	b.y_distance = ft_abs(pos[1] - pos[3]);
	b.x_direction = ft_find_direction(pos[0], pos[2]);
	b.y_direction = ft_find_direction(pos[1], pos[3]);
	b.err = b.x_distance - b.y_distance;
	while (pos[0] != pos[2] || pos[1] != pos[3])
	{
		ft_put_pixel_to_image(env, pos[0], pos[1], color);
		b.err2 = 2 * b.err;
		if (b.err2 > -b.y_distance)
		{
			b.err -= b.y_distance;
			pos[0] += b.x_direction;
		}
		if (b.err2 < b.x_distance)
		{
			b.err += b.x_distance;
			pos[1] += b.y_direction;
		}
	}
}

void	ft_draw(t_fdf *env)
{
	int	x;
	int	y;
	int	pos[4];

	y = -1;
	while (++y < env->map->height)
	{
		x = -1;
		while (++x < env->map->width)
		{
			pos[0] = x;
			pos[1] = y;
			pos[2] = x + 1;
			pos[3] = y;
			if (x + 1 < env->map->width)
				ft_draw_line(env, pos, env->map->points[y][x].color);
			pos[0] = x;
			pos[1] = y;
			pos[2] = x;
			pos[3] = y + 1;
			if (y + 1 < env->map->height)
				ft_draw_line(env, pos, env->map->points[y][x].color);
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
