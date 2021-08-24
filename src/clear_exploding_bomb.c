/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exploding_bomb.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 00:36:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/24 04:39:27 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	sl_clear_upper_segment(t_env *env, char *map[], int x, int y)
{
	int	i;
	int	size;

	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= size && (env->tex.bomb.pos.y - i > 0) && map[env->tex.bomb.pos.y - i][env->tex.bomb.pos.x] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x, y - i * BLOC_LEN);
		++i;
	}
}

static void	sl_clear_lower_segment(t_env *env, char *map[], int x, int y)
{
	int	height;
	int	size;
	int	i;

	height = env->height;
	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= size && (env->tex.bomb.pos.y + i < height) && map[env->tex.bomb.pos.y + i][env->tex.bomb.pos.x] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x, y + i * BLOC_LEN);
		++i;
	}
}

static void	sl_clear_left_segment(t_env *env, char *map[], int x, int y)
{
	int	i;
	int	size;

	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= size && (env->tex.bomb.pos.x - 1 > 0) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x - 1] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x - i * BLOC_LEN, y);
		++i;
	}
}

static void	sl_clear_right_segment(t_env *env, char *map[], int x, int y)
{
	int	width;
	int	size;
	int	i;

	width = env->width;
	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= size && (env->tex.bomb.pos.x + 1 < width) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x + 1] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x + i * BLOC_LEN, y);
		++i;
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
