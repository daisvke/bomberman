/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomb_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 00:36:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/04 04:49:27 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	sl_clear_upper_segment(\
	t_env *env, t_items *bomb, char *map[], t_coord pos)
{
	t_coord	coord;
	int		x;
	int		y;
	int		size;
	int		i;

	x = pos.x / BLOC_LEN;
	y = pos.y / BLOC_LEN;
	size = bomb->explode_size;
	i = 1;
	while (i <= size && (y - i > 0) && map[y - i][x] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x, pos.y - i * BLOC_LEN);
		sl_replace_with_green_tile(env, coord);
		++i;
	}
}

static void	sl_clear_lower_segment(\
	t_env *env, t_items *bomb, char *map[], t_coord pos)
{
	t_coord	coord;
	int		x;
	int		y;
	int		size;
	int		i;

	x = pos.x / BLOC_LEN;
	y = pos.y / BLOC_LEN;
	size = bomb->explode_size;
	i = 1;
	while (i <= size && (y + i < env->height) && map[y + i][x] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x, pos.y + i * BLOC_LEN);
		sl_replace_with_green_tile(env, coord);
		++i;
	}
}

static void	sl_clear_left_segment(
	t_env *env, t_items *bomb, char *map[], t_coord pos)
{
	t_coord	coord;
	int		x;
	int		y;
	int		size;
	int		i;

	x = pos.x / BLOC_LEN;
	y = pos.y / BLOC_LEN;
	size = bomb->explode_size;
	i = 1;
	while (i <= size && (x - i > 0) && map[y][x - i] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x - i * BLOC_LEN, pos.y);
		sl_replace_with_green_tile(env, coord);
		++i;
	}
}

static void	sl_clear_right_segment(\
	t_env *env, t_items *bomb, char *map[], t_coord pos)
{
	t_coord	coord;
	int		x;
	int		y;
	int		size;
	int		i;

	x = pos.x / BLOC_LEN;
	y = pos.y / BLOC_LEN;
	size = bomb->explode_size;
	i = 1;
	while (i <= size && (x + i < env->width) && map[y][x + i] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x + i * BLOC_LEN, pos.y);
		sl_replace_with_green_tile(env, coord);
		++i;
	}
}

void	sl_clear_segments_of_exploding_bomb(\
	t_env *env, t_items *bomb, t_coord pos)
{
	char		**map;

	map = env->map;
	sl_replace_with_green_tile(env, pos);
	sl_clear_upper_segment(env, bomb, map, pos);
	sl_clear_lower_segment(env, bomb, map, pos);
	sl_clear_left_segment(env, bomb, map, pos);
	sl_clear_right_segment(env, bomb, map, pos);
}
