/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 20:21:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/24 07:32:45 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_find_which_ennemy_is_dead(t_env *env, int x_start, int y)
{
	int			ennemies_count;
	int			i;

	ennemies_count = env->tex.ennemies.count;
	i = 0;
	while (i < ennemies_count)
	{
		if (env->tex.ennemies.sprites[i].pos.x == x_start && env->tex.ennemies.sprites[i].pos.y == y)
			env->tex.ennemies.sprites[i].alive = false;
		++i;
	}
	env->map[y][x_start] = MAP_FLOOR;
}

bool	sl_check_if_sprite_is_dead(t_env *env, char *map[], int  x, int y)
{
	int	p1_x;
	int	p1_y;
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
	int	size;
	int	collectible;

	size = env->tex.bomb.explode_size;
	p1_x = env->p1.pos.x;
	p1_y = env->p1.pos.y; 
	x_start = x - size;
	if (x_start < 0)
		x_start = 0;
	x_end = x + size;
	if (x_end > env->width)
		x_end = env->width;
	y_start = y - size;
	if (y_start < 0)
		y_start = 0;
	y_end = y + size;
	if (y_end > env->height)
		y_end = env->height;
	while (x_start < x_end)
	{
		if (map[y][x_start] == MAP_PLAYER)
			return (true);
		if (map[y][x_start] == MAP_ENNEMY)
			sl_find_which_ennemy_is_dead(env, x_start, y);
		collectible = sl_is_collectible(map[y][x_start]);
		if (map[y][x_start] != MAP_WALL)
			map[y][x_start] = MAP_FLOOR;
		if (collectible == 1)
			sl_find_and_turn_off_item(env->tex.bomb.item_bombs, env->tex.bomb.to_collect, x_start, y);
		if (collectible == 2)
			sl_find_and_turn_off_item(env->tex.fire.items, env->tex.fire.to_collect, x_start, y);
		if (collectible == 3)
			sl_find_and_turn_off_item(env->tex.speed.items, env->tex.speed.to_collect, x_start, y);
		++x_start;
	}
	while (y_start < y_end)
	{
		if (map[y_start][x] == MAP_PLAYER)
			return (true);
		collectible = sl_is_collectible(map[y_start][x]);
		if (map[y_start][x] != MAP_WALL)
			map[y_start][x] = MAP_FLOOR;
		if (collectible == 1)
			sl_find_and_turn_off_item(env->tex.bomb.item_bombs, env->tex.bomb.to_collect, x, y_start);
		if (collectible == 2)
			sl_find_and_turn_off_item(env->tex.fire.items, env->tex.fire.to_collect, x, y_start);
		if (collectible == 3)
			sl_find_and_turn_off_item(env->tex.speed.items, env->tex.speed.to_collect, x, y_start);
		++y_start;
	}
	return (false);
}

void	sl_explode_bomb(t_env *env, int x, int y, int *i, int *j)
{
	static int	k;
	bool		is_dead;

	if (k <= CENTER_MESS_TIME)
		sl_draw_segments_of_exploding_bomb(env, x, y);
	is_dead = sl_check_if_sprite_is_dead(env, env->map, x / BLOC_LEN, y / BLOC_LEN);
	++k;
	if (k > CENTER_MESS_TIME)
	{
		*i = 0;
		*j = 0;
		k = 0;
		sl_clear_segments_of_exploding_bomb(env, x, y);
		env->tex.bomb.pos.x = 0;
		env->tex.bomb.pos.y = 0;
		env->tex.bomb.set_bomb = false;
		if (is_dead)
			env->p1.alive = false;
	}
}

void    sl_set_bomb(t_env *env)
{
    static int	i;
	static int	j;
	int			bomb_pos_x;
	int			bomb_pos_y;
	t_states	set_bomb;		

	set_bomb = env->tex.bomb.set_states;
	bomb_pos_x = env->tex.bomb.pos.x * BLOC_LEN;
	bomb_pos_y = env->tex.bomb.pos.y * BLOC_LEN;
    if (i <= 1280)
    {
        if (i % 320 == 0)
			++j;
		if (j % 2 == 0)
			sl_render_bloc_with_xpm(&env->bkgd, &set_bomb.one, bomb_pos_x, bomb_pos_y);
		else
		{
			sl_replace_with_green_tile(env, bomb_pos_x, bomb_pos_y);
			sl_render_bloc_with_xpm(&env->bkgd, &set_bomb.three, bomb_pos_x, bomb_pos_y);
		}
        ++i;
    }
	if (i > 1280)
		sl_explode_bomb(env, bomb_pos_x, bomb_pos_y, &i, &j);
}
