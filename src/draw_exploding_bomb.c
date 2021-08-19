/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_exploding_bomb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 05:35:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/19 06:19:47 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	sl_draw_upper_segment(t_env *env, char *map[], t_explode_states states, int x, int y)
{
	if ((env->tex.bomb.pos.y - 1 > 0) && map[env->tex.bomb.pos.y - 1][env->tex.bomb.pos.x] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.one, x, y - BLOC_LEN);
		if ((env->tex.bomb.pos.y - 2 > 0) && map[env->tex.bomb.pos.y - 2][env->tex.bomb.pos.x] != MAP_WALL)
			sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.two, x, y - 2 * BLOC_LEN);
	}
}

static void	sl_draw_lower_segment(t_env *env, char *map[], t_explode_states states, int x, int y)
{
	int	height;

	height = env->height;
	if ((env->tex.bomb.pos.y + 1 < height) && map[env->tex.bomb.pos.y + 1][env->tex.bomb.pos.x] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.one, x, y + BLOC_LEN);
		if ((env->tex.bomb.pos.y + 2 < height) && map[env->tex.bomb.pos.y + 2][env->tex.bomb.pos.x] != MAP_WALL)
			sl_render_bloc_with_xpm(&env->bkgd, &states.vrt.three, x, y + 2 * BLOC_LEN);
	}
}

static void	sl_draw_left_segment(t_env *env, char *map[], t_explode_states states, int x, int y)
{
	if ((env->tex.bomb.pos.x - 1 > 0) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x - 1] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.one, x - BLOC_LEN, y);
		if ((env->tex.bomb.pos.x - 2 > 0) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x - 2] != MAP_WALL)
			sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.two, x - 2 * BLOC_LEN, y);
	}
}

static void	sl_draw_right_segment(t_env *env, char *map[], t_explode_states states, int x, int y)
{
	int	width;

	width = env->width;
	if ((env->tex.bomb.pos.x + 1 < width) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x + 1] != MAP_WALL)
	{
		sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.one, x + BLOC_LEN, y);
		if ((env->tex.bomb.pos.x + 2 < width) && map[env->tex.bomb.pos.y][env->tex.bomb.pos.x + 2] != MAP_WALL)
			sl_render_bloc_with_xpm(&env->bkgd, &states.hrz.three, x + 2 * BLOC_LEN, y);
	}
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
