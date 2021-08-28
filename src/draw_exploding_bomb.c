/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_exploding_bomb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 05:35:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/28 04:00:17 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	sl_draw_upper_segment(t_env *env, t_items *bomb, char *map[], t_explode_states states, int x, int y)
{
	int	map_x;
	int	map_y;
	int	i;
	int	size;

	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	size = bomb->explode_size;
	i = 1;
	while (i <= (size - 1) && (map_y - i > 0) && map[map_y - i][map_x] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.one, x, y - i * BLOC_LEN);
		++i;
	}
	if (map[map_y - i][map_x] != MAP_WALL)
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.two, x, y - i * BLOC_LEN);
}

static void	sl_draw_lower_segment(t_env *env, t_items *bomb, char *map[], t_explode_states states, int x, int y)
{
	int	map_x;
	int	map_y;
	int	height;
	int	size;
	int	i;

	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	height = env->height;
	size = bomb->explode_size;
	i = 1;
	while (i <= (size - 1) && (map_y + i < height) && map[map_y + i][map_x] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.one, x, y + i * BLOC_LEN);
		++i;
	}
	if ((map_y + i < height) && map[map_y + i][map_x] != MAP_WALL)
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.three, x, y + i * BLOC_LEN);
}

static void	sl_draw_left_segment(t_env *env, t_items *bomb, char *map[], t_explode_states states, int x, int y)
{
	int	map_x;
	int	map_y;
	int	i;
	int	size;

	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	size = bomb->explode_size;
	i = 1;
	while (i <= (size - 1) && (map_x - i > 0) && map[map_y][map_x - i] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.one, x - i * BLOC_LEN, y);
		++i;
	}
	if ((map_x - i > 0) && map[map_y][map_x - i] != MAP_WALL)
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.two, x - i * BLOC_LEN, y);
}

static void	sl_draw_right_segment(t_env *env, t_items *bomb, char *map[], t_explode_states states, int x, int y)
{
	int	map_x;
	int	map_y;
	int	width;
	int	size;
	int	i;

	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	width = env->width;
	size = bomb->explode_size;
	i = 1;
	while (i <= (size - 1) && (map_x + i < width) && map[map_y][map_x + i] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.one, x + i * BLOC_LEN, y);
		++i;
	}
	if ((map_x + i < width) && map[map_y][map_x + i] != MAP_WALL)
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.three, x + i * BLOC_LEN, y);
}

void	sl_draw_segments_of_exploding_bomb(t_env *env, t_items *bomb, int x, int y)
{
	t_explode_states	bomb_states;
	char		**map;

	bomb_states = env->tex.bomb.explode_states;
	map = env->map;
	sl_render_bloc_with_xpm(&env->bkgd, &bomb_states.ctr, x, y);
	sl_draw_upper_segment(env, bomb, map, bomb_states, x, y);
	sl_draw_lower_segment(env, bomb, map, bomb_states, x, y);
	sl_draw_left_segment(env, bomb, map, bomb_states, x, y);
	sl_draw_right_segment(env, bomb, map, bomb_states, x, y);
}
