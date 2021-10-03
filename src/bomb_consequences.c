/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomb_consequences.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:55:47 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/03 20:53:09 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	sl_check_up_for_consequences(t_env *env, t_coord pos, int size)
{
	char	**map;
	int		x;
	int		y;
	int		y_start;
	int		y_end;

	map = env->map;
	x = pos.x;
	y = pos.y;
	y_start = y;
	y_end = y + size;
	if (y_end > env->height)
		y_end = env->height;
	while (y_start <= y_end && map[y_start][x] != MAP_WALL)
	{
		sl_check_each_element(env, map, x, y_start);
		++y_start;
	}
}

void	sl_check_bottom_for_consequences(t_env *env, t_coord pos, int size)
{
	char	**map;
	int		x;
	int		y;
	int		y_start;
	int		y_end;

	map = env->map;
	x = pos.x;
	y = pos.y;
	y_start = y;
	y_end = y - size;
	if (y_end < 0)
		y_end = 0;
	while (y_start >= y_end && map[y_start][x] != MAP_WALL)
	{
		sl_check_each_element(env, map, x, y_start);
		--y_start;
	}
}

void	sl_check_left_for_consequences(t_env *env, t_coord pos, int size)
{
	char	**map;
	int		x;
	int		y;
	int		x_start;
	int		x_end;

	map = env->map;
	x = pos.x;
	y = pos.y;
	x_start = x;
	x_end = x - size;
	if (x_end < 0)
		x_end = 0;
	while (x_start >= x_end && map[y][x_start] != MAP_WALL)
	{
		sl_check_each_element(env, map, x_start, y);
		--x_start;
	}
}

void	sl_check_right_for_consequences(t_env *env, t_coord pos, int size)
{
	char	**map;
	int		x;
	int		y;
	int		x_start;
	int		x_end;

	map = env->map;
	x = pos.x;
	y = pos.y;
	x_start = x;
	x_end = x + size;
	if (x_end > env->width)
		x_end = env->width;
	while (x_start <= x_end && map[y][x_start] != MAP_WALL)
	{
		sl_check_each_element(env, map, x_start, y);
		++x_start;
	}
}

void	sl_check_what_is_affected_by_the_explosion(t_env *env, t_items *bomb, \
	t_coord pos)
{
	int	p1_x;
	int	p1_y;
	int	size;

	size = bomb->explode_size;
	p1_x = env->p1.pos.x;
	p1_y = env->p1.pos.y;
	sl_check_up_for_consequences(env, pos, size);
	sl_check_bottom_for_consequences(env, pos, size);
	sl_check_left_for_consequences(env, pos, size);
	sl_check_right_for_consequences(env, pos, size);
}
