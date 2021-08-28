/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exploding_bomb.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 00:36:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/26 03:35:45 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	sl_clear_upper_segment(t_env *env, char *map[], int x, int y)
{
	int	map_x;
	int	map_y;
	int	i;
	int	size;

	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= size && (map_y - i > 0) && map[map_y - i][map_x] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x, y - i * BLOC_LEN);
		++i;
	}
}

static void	sl_clear_lower_segment(t_env *env, char *map[], int x, int y)
{
	int	map_x;
	int	map_y;
	int	height;
	int	size;
	int	i;

	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	height = env->height;
	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= size && (map_y + i < height) && map[map_y + i][map_x] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x, y + i * BLOC_LEN);
		++i;
	}
}

static void	sl_clear_left_segment(t_env *env, char *map[], int x, int y)
{
	int	map_x;
	int	map_y;
	int	i;
	int	size;

	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= size && (map_x - i > 0) && map[map_y][map_x - i] != MAP_WALL)
	{
		sl_replace_with_green_tile(env, x - i * BLOC_LEN, y);
		++i;
	}
}

static void	sl_clear_right_segment(t_env *env, char *map[], int x, int y)
{
	int	map_x;
	int	map_y;
	int	width;
	int	size;
	int	i;

	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	width = env->width;
	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= size && (map_x + i < width) && map[map_y][map_x + i] != MAP_WALL)
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
