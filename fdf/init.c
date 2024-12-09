/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:04:47 by kgiraud           #+#    #+#             */
/*   Updated: 2024/12/02 16:34:30 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_get_width(char *s, t_fdf *env)
{
	char	**split;
	int		width;
	int		error;

	width = 0;
	error = 0;
	split = ft_split(s, ' ');
	if (!split)
		return_error("Split error", env);
	while (split[width])
	{
		if (!split[width][0] || (split[width][0] >= 9 && split[width][0] <= 13)
			|| split[width][0] == 32)
			error++;
		free(split[width]);
		width++;
	}
	free(split);
	return (width - error);
}

void	ft_get_map_dimensions(char *file_name, int *width,
		int *height, t_fdf *env)
{
	int		fd;
	char	*line;
	int		tmp_width;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return_error("Creation fd error", env);
	while (get_next_line(fd, &line) > 0)
	{
		tmp_width = ft_get_width(line, env);
		if (*width == 0)
			*width = tmp_width;
		else if (*width != tmp_width)
			return_error("Irregular width map error", env);
		(*height)++;
		free(line);
	}
	close(fd);
}

t_map	*ft_map_init(char *file_name, t_fdf *env)
{
	int		i;
	t_map	*map;

	i = 0;
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return_error("Malloc struct map error", env);
	map->width = 0;
	map->height = 0;
	ft_get_map_dimensions(file_name, &map->width, &map->height, env);
	map->points = (t_point **)malloc(sizeof(t_point *) * (map->height));
	if (!map->points)
		return_error("Malloc map *points error", env);
	while (i < map->height)
	{
		map->points[i] = (t_point *)malloc(sizeof(t_point) * map->width);
		if (!map->points[i])
			return_error("Malloc map **points error", env);
		i++;
	}
	map->def_color = 0xFFFFFF;
	return (map);
}

t_camera	*ft_camera_init(t_fdf *env)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		return_error("Malloc cam error", env);
	cam->zoom = ft_min((WIDTH / env->map->width / 2),
			(HEIGHT / env->map->height / 2));
	if (cam->zoom == 0)
		cam->zoom = 1;
	cam->z_height = 1;
	cam->add_shift_x = 0;
	cam->add_shift_y = 0;
	cam->angle = M_PI / 6;
	return (cam);
}

t_fdf	*ft_env_init(char *file_name)
{
	t_fdf	*env;

	env = (t_fdf *)malloc(sizeof(t_fdf));
	if (!env)
		return_error("Malloc env error", env);
	env->mlx = mlx_init();
	if (!env->mlx)
		return_error("Mlx init error", env);
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, file_name);
	if (!env->win)
		return_error("Mlx new window error", env);
	env->map = ft_map_init(file_name, env);
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bpp,
			&env->size_line, &env->endian);
	env->camera = ft_camera_init(env);
	if (!env->camera)
		return_error("Malloc camera error", env);
	return (env);
}
