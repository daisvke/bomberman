/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_interactions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:03:39 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/16 03:37:31 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_find_and_turn_off_item(t_items *items, int max, int x, int y)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (items[i].pos.x == x && items[i].pos.y == y)
			items[i].draw = false;
		++i;
	}
}

void	sl_collect_bomb(t_env *env, char **map, int x, int y)
{	
	int	collected;
	int	to_collect;

	collected = env->tex.bomb.collected;
	to_collect = env->tex.bomb.to_collect;
	if (map[y][x] == MAP_ITEM_BOMB)
	{
		sl_find_and_turn_off_item(env->tex.bomb.item_bombs, to_collect, x, y);
		map[y][x] = MAP_FLOOR;
		++env->tex.bomb.collected;
		env->tex.bomb.set_bombs[collected].draw = false;
		env->tex.bomb.set_bombs[collected].pos.x = 0;
		env->tex.bomb.set_bombs[collected].pos.y = 0;
		env->tex.bomb.set_bombs[collected].time1 = 0;
		env->tex.bomb.set_bombs[collected].time2 = 0;
		env->tex.bomb.set_bombs[collected].time3 = 0;
	}
}

void	sl_collect_fire(t_env *env, char **map, int x, int y)
{	
	if (map[y][x] == MAP_FIRE)
	{
		sl_find_and_turn_off_item(env->tex.fire.items, env->tex.fire.to_collect, x, y);
		map[y][x] = MAP_FLOOR;
		++env->tex.bomb.explode_size;
	}
}

void	sl_collect_speed(t_env *env, char **map, int x, int y)
{	
	if (map[y][x] == MAP_SPEED)
	{
		sl_find_and_turn_off_item(env->tex.speed.items, env->tex.speed.to_collect, x, y);
		map[y][x] = MAP_FLOOR;
		if (env->p1.speed >= 30)
			env->p1.speed -= 20;
	}
}

void	sl_handle_textures_while_moving(t_env *env, int apply_to, t_coord delta)
{
	char	**map;
	int		x;
	int		y;

	map = env->map;
	x = env->p1.pos.x + delta.x;
	y = env->p1.pos.y + delta.y;
	if (apply_to == PLAYER)
	{
		sl_collect_bomb(env, map, x, y);
		sl_collect_fire(env, map, x, y);
		sl_collect_speed(env, map, x, y);
		if (env->tex.bomb.collected - START_BOMB == env->tex.bomb.to_collect)
			if (map[y][x] == MAP_EXIT)
				env->game_clear = true;	
	}
}
