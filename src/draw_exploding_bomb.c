/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_exploding_bomb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 05:35:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/24 04:32:34 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	sl_draw_upper_segment(t_env *env, char *map[], t_explode_states states, int x, int y)
{
	int	i;
	int	size;

	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= (size - 1) && (env->tex.bomb.pos.y - i > 0) && map[env->tex.bomb.pos.y - i][env->tex.bomb.pos.x] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.one, x, y - i * BLOC_LEN);
		++i;
	}
	if (map[env->tex.bomb.pos.y - i][env->tex.bomb.pos.x] != MAP_WALL)
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.two, x, y - i * BLOC_LEN);
}

static void	sl_draw_lower_segment(t_env *env, char *map[], t_explode_states states, int x, int y)
{
	int	height;
	int	size;
	int	i;

	height = env->height;
	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= (size - 1) && (env->tex.bomb.pos.y + i < height) && map[env->tex.bomb.pos.y + i][env->tex.bomb.pos.x] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.one, x, y + i * BLOC_LEN);
		++i;
	}
	if ((env->tex.bomb.pos.y + i < height) && map[env->tex.bomb.pos.y + i][env->tex.bomb.pos.x] != MAP_WALL)
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.three, x, y + i * BLOC_LEN);
}

static void	sl_draw_left_segment(t_env *env, char *map[], t_explode_states states, int x, int y)
{
	int	i;
	int	size;

	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= (size - 1) && (env->tex.bomb.pos.x - 1 > 0) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x - 1] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.one, x - i * BLOC_LEN, y);
		++i;
	}
	if ((env->tex.bomb.pos.x - i > 0) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x - i] != MAP_WALL)
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.two, x - i * BLOC_LEN, y);
}

static void	sl_draw_right_segment(t_env *env, char *map[], t_explode_states states, int x, int y)
{
	int	width;
	int	size;
	int	i;

	width = env->width;
	size = env->tex.bomb.explode_size;
	i = 1;
	while (i <= (size - 1) && (env->tex.bomb.pos.x + 1 < width) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x + 1] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.one, x + i * BLOC_LEN, y);
		++i;
	}
	if ((env->tex.bomb.pos.x + i < width) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x + i] != MAP_WALL)
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.three, x + i * BLOC_LEN, y);
}

void	sl_draw_segments_of_exploding_bomb(t_env *env, int x, int y)
{
	t_explode_states	bomb_states;
	char		**map;

	bomb_states = env->tex.bomb.explode_states;
	map = env->map;
	sl_render_bloc_with_xpm(&env->bkgd, &bomb_states.ctr, x, y);
	sl_draw_upper_segment(env, map, bomb_states, x, y);
	sl_draw_lower_segment(env, map, bomb_states, x, y);
	sl_draw_left_segment(env, map, bomb_states, x, y);
	sl_draw_right_segment(env, map, bomb_states, x, y);
}
