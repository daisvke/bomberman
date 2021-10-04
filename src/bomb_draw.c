/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomb_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 05:35:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/04 04:50:01 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	sl_draw_upper_segment(\
	t_env *env, t_items *bomb, t_explode_states states, t_coord pos)
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
	while (i <= (size - 1) && (y - i > 0) && env->map[y - i][x] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x, pos.y - i * BLOC_LEN);
		sl_render_bloc_with_xpm(&env->canvas, &states.vrt.one, coord, true);
		++i;
	}
	if (env->map[y - i][x] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x, pos.y - i * BLOC_LEN);
		sl_render_bloc_with_xpm(&env->canvas, &states.vrt.two, coord, true);
	}
}

static void	sl_draw_lower_segment(\
	t_env *env, t_items *bomb, t_explode_states states, t_coord pos)
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
	while (i <= (size - 1) && y + i < env->height \
		&& env->map[y + i][x] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x, pos.y + i * BLOC_LEN);
		sl_render_bloc_with_xpm(&env->canvas, &states.vrt.one, coord, true);
		++i;
	}
	if ((y + i < env->height) && env->map[y + i][x] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x, pos.y + i * BLOC_LEN);
		sl_render_bloc_with_xpm(&env->canvas, &states.vrt.three, coord, true);
	}
}

static void	sl_draw_left_segment(\
	t_env *env, t_items *bomb, t_explode_states states, t_coord pos)
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
	while (i <= (size - 1) && (x - i > 0) && env->map[y][x - i] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x - i * BLOC_LEN, pos.y);
		sl_render_bloc_with_xpm(&env->canvas, &states.hrz.one, coord, true);
		++i;
	}
	if ((x - i > 0) && env->map[y][x - i] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x - i * BLOC_LEN, pos.y);
		sl_render_bloc_with_xpm(&env->canvas, &states.hrz.two, coord, true);
	}
}

static void	sl_draw_right_segment(\
	t_env *env, t_items *bomb, t_explode_states states, t_coord pos)
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
	while (i <= (size - 1) && (x + i < env->width) \
		&& env->map[y][x + i] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x + i * BLOC_LEN, pos.y);
		sl_render_bloc_with_xpm(&env->canvas, &states.hrz.one, coord, true);
		++i;
	}
	if ((x + i < env->width) && env->map[y][x + i] != MAP_WALL)
	{
		coord = sl_assign_pos(pos.x + i * BLOC_LEN, pos.y);
		sl_render_bloc_with_xpm(&env->canvas, &states.hrz.three, coord, true);
	}
}

void	sl_draw_segments_of_exploding_bomb(\
	t_env *env, t_items *bomb, t_coord pos)
{
	t_explode_states	bomb_states;

	bomb_states = env->tex.bomb.explode_states;
	sl_render_bloc_with_xpm(&env->canvas, &bomb_states.ctr, pos, true);
	sl_draw_upper_segment(env, bomb, bomb_states, pos);
	sl_draw_lower_segment(env, bomb, bomb_states, pos);
	sl_draw_left_segment(env, bomb, bomb_states, pos);
	sl_draw_right_segment(env, bomb, bomb_states, pos);
}
