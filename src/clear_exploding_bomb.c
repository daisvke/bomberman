/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exploding_bomb.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 00:36:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/23 02:30:14 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	sl_clear_upper_segment(t_env *env, char *map[], int x, int y)
{
	if ((env->tex.bomb.pos.y - 1 > 0) && map[env->tex.bomb.pos.y - 1][env->tex.bomb.pos.x] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x, y - BLOC_LEN);
		if ((env->tex.bomb.pos.y - 2 > 0) && map[env->tex.bomb.pos.y - 2][env->tex.bomb.pos.x] != MAP_WALL)
			sl_replace_with_green_tile(env, x, y - 2 * BLOC_LEN);
	}
}

static void	sl_clear_lower_segment(t_env *env, char *map[], int x, int y)
{
	int	height;

	height = env->height;
	if ((env->tex.bomb.pos.y + 1 < height) && map[env->tex.bomb.pos.y + 1][env->tex.bomb.pos.x] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x, y + BLOC_LEN);
		if ((env->tex.bomb.pos.y + 2 < height) && map[env->tex.bomb.pos.y + 2][env->tex.bomb.pos.x] != MAP_WALL)
			sl_replace_with_green_tile(env, x, y + 2 * BLOC_LEN);
	}
}

static void	sl_clear_left_segment(t_env *env, char *map[], int x, int y)
{
	if ((env->tex.bomb.pos.x - 1 > 0) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x - 1] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x - BLOC_LEN, y);
		if ((env->tex.bomb.pos.x - 2 > 0) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x - 2] != MAP_WALL)
			sl_replace_with_green_tile(env, x - 2 * BLOC_LEN, y);
	}
}

static void	sl_clear_right_segment(t_env *env, char *map[], int x, int y)
{
	int	width;

	width = env->width;
	if ((env->tex.bomb.pos.x + 1 < width) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x + 1] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x + BLOC_LEN, y);
		if ((env->tex.bomb.pos.x + 2 < width) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x + 2] != MAP_WALL)
			sl_replace_with_green_tile(env, x + 2 * BLOC_LEN, y);
	}
}

void	sl_clear_segments_of_exploding_bomb(t_env *env, int x, int y)
{
	char		**map;

	map = env->map;
	sl_replace_with_green_tile(env, x, y);
	sl_clear_upper_segment(env, map, x, y);
	sl_clear_lower_segment(env, map, x, y);
	sl_clear_left_segment(env, map, x, y);
	sl_clear_right_segment(env, map, x, y);
}
