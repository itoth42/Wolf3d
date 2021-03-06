/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 20:55:03 by itoth             #+#    #+#             */
/*   Updated: 2017/07/03 20:55:04 by itoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}

static void			correct_vertical_collisions(t_point *now, t_point *possible
												, double angle, t_map *map)
{
	int				x;
	int				y;

	x = (int)floor(now->x) + POINTS_RIGHT(angle);
	y = (int)floor(now->y);
	if (map->data[y][x] && map->data[y + 1][x]
		&& ft_abs_double(x - possible->x) < WALL_DISTANCE)
		possible->x = x + WALL_DISTANCE * (POINTS_RIGHT(angle) ? -1 : 1);
}

static void			correct_horizontal_collisions(t_point *now
													, t_point *possible
													, double angle, t_map *map)
{
	int				x;
	int				y;

	x = (int)floor(now->x);
	y = (int)floor(now->y) + POINTS_DOWN(angle);
	if (map->data[y][x] && map->data[y][x + 1]
		&& ft_abs_double(y - possible->y) < WALL_DISTANCE)
		possible->y = y + WALL_DISTANCE * (POINTS_DOWN(angle) ? -1 : 1);
}

void				move_camera(double angle, t_environment *env)
{
	t_point			possible;

	normalize_angle(&angle);
	possible.x = env->camera.location.x + VELOCITY * cos(-angle);
	possible.y = env->camera.location.y + VELOCITY * sin(-angle);
	if (possible.x > env->map->width - 1 - WALL_DISTANCE)
		possible.x = env->map->width - 1 - WALL_DISTANCE;
	else if (possible.x < WALL_DISTANCE)
		possible.x = WALL_DISTANCE;
	if (possible.y > env->map->height - 1 - WALL_DISTANCE)
		possible.y = env->map->height - 1 - WALL_DISTANCE;
	else if (possible.y < WALL_DISTANCE)
		possible.y = WALL_DISTANCE;
	correct_vertical_collisions(&env->camera.location, &possible
								, angle, env->map);
	correct_horizontal_collisions(&env->camera.location, &possible
								, angle, env->map);
	env->camera.location = possible;
	draw(env);
}
