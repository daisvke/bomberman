/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomb_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 20:21:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/03 21:25:32 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_find_which_ennemy_is_dead(t_env *env, int x, int y)
{
	int	ennemies_count;
	int	ennemy_x;
	int	ennemy_y;
	int	i;

	ennemies_count = env->tex.ennemies.count;
	i = 0;
	while (i < ennemies_count)
	{
		ennemy_x = env->tex.ennemies.sprites[i].pos.x;
		ennemy_y = env->tex.ennemies.sprites[i].pos.y;
		if (ennemy_x == x && ennemy_y == y)
			env->tex.ennemies.sprites[i].alive = false;
		++i;
	}
	env->map[y][x] = MAP_FLOOR;
}

void	sl_check_each_element(t_env *env, char **map, int x, int y)
{
	t_bombs	*bomb;
	t_item	*fire;
	t_item	*speed;
	int		collectible;

	bomb = &env->tex.bomb;
	fire = &env->tex.fire;
	speed = &env->tex.speed;
	if (map[y][x] == MAP_PLAYER)
		env->p1.alive = false;
	if (map[y][x] == MAP_ENNEMY)
		sl_find_which_ennemy_is_dead(env, x, y);
	if (map[y][x] != MAP_WALL)
		map[y][x] = MAP_FLOOR;
	collectible = sl_is_collectible(map[y][x]);
	if (collectible == 1)
	{
		sl_find_and_turn_off_item(bomb->item_bombs, bomb->to_collect, x, y);
		--bomb->to_collect;
	}
	if (collectible == 2)
		sl_find_and_turn_off_item(fire->items, fire->to_collect, x, y);
	if (collectible == 3)
		sl_find_and_turn_off_item(speed->items, speed->to_collect, x, y);
}

void	sl_explode_bomb(t_env *env, t_items *bomb, t_coord pos)
{
	t_coord	coord;
	t_coord	init_pos;

	if (bomb->time3 <= BOMB_EXPLODE_TIME)
	{
		coord = sl_assign_pos(pos.x / BLOC_LEN, pos.y / BLOC_LEN);
		sl_check_what_is_affected_by_the_explosion(env, bomb, coord);
		sl_draw_segments_of_exploding_bomb(env, bomb, pos);
		++bomb->time3;
	}
	else
	{
		sl_clear_segments_of_exploding_bomb(env, bomb, pos);
		init_pos = sl_assign_pos(0, 0);
		sl_init_set_bomb(bomb, false, init_pos, 0);
		--env->tex.bomb.set_bombs_nbr;
	}
}

void	sl_set_bomb(t_env *env, t_items *bomb)
{
	t_coord		pos;
	t_states	set_bomb;		

	set_bomb = env->tex.bomb.set_states;
	pos = sl_assign_pos(bomb->pos.x * BLOC_LEN, bomb->pos.y * BLOC_LEN);
	if (bomb->time1 <= BOMB_SET_TIME)
	{
		if (bomb->time1 % 320 == 0)
			++bomb->time2;
		if (bomb->time2 % 2 == 0)
			sl_render_bloc_with_xpm(&env->canvas, &set_bomb.one, pos, true);
		else
		{
			sl_replace_with_green_tile(env, pos);
			sl_render_bloc_with_xpm(&env->canvas, &set_bomb.three, pos, true);
		}
		++bomb->time1;
	}
	else
		sl_explode_bomb(env, bomb, pos);
}
