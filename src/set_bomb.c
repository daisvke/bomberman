/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 20:21:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/31 05:30:43 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_find_which_ennemy_is_dead(t_env *env, int x, int y)
{
	int			ennemies_count;
	int			i;

	ennemies_count = env->tex.ennemies.count;
	i = 0;
	while (i < ennemies_count)
	{
		if (env->tex.ennemies.sprites[i].pos.x == x && env->tex.ennemies.sprites[i].pos.y == y)
			env->tex.ennemies.sprites[i].alive = false;
		++i;
	}
	env->map[y][x] = MAP_FLOOR;
}

void	sl_check_each_element(t_env *env, int x, int y)
{
	char	**map;
	int		collectible;

	map = env->map;
	if (map[y][x] == MAP_PLAYER)
		env->p1.alive = false;
	if (map[y][x] == MAP_ENNEMY)
		sl_find_which_ennemy_is_dead(env, x, y);
	collectible = sl_is_collectible(map[y][x]);
	if (map[y][x] != MAP_WALL)
		map[y][x] = MAP_FLOOR;
	if (collectible == 1)
	{
		sl_find_and_turn_off_item(env->tex.bomb.item_bombs, env->tex.bomb.to_collect, x, y);
		--env->tex.bomb.to_collect;
	}
	if (collectible == 2)
		sl_find_and_turn_off_item(env->tex.fire.items, env->tex.fire.to_collect, x, y);
	if (collectible == 3)
		sl_find_and_turn_off_item(env->tex.speed.items, env->tex.speed.to_collect, x, y);
}

bool	sl_check_what_is_affected_by_the_explosion(t_env *env, t_items *bomb, char *map[], int  x, int y)
{
	int	p1_x;
	int	p1_y;
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
	int	size;

	size = bomb->explode_size;
	p1_x = env->p1.pos.x;
	p1_y = env->p1.pos.y; 
	x_start = x;
	x_end = x - size;
	if (x_end < 0)
		x_end = 0;
	while (x_start > x_end && map[y][x_start] != MAP_WALL)
	{
		sl_check_each_element(env, x_start, y);
		--x_start;
	}
	x_start = x;
	x_end = x + size;
	if (x_end > env->width)
		x_end = env->width;
	while (x_start < x_end && map[y][x_start] != MAP_WALL)
	{
		sl_check_each_element(env, x_start, y);
		++x_start;
	}
	y_start = y;
	y_end = y - size;
	if (y_end < 0)
		y_end = 0;
	while (y_start > y_end && map[y_start][x] != MAP_WALL)
	{
		sl_check_each_element(env, x, y_start);
		--y_start;
	}
	y_start = y;
	y_end = y + size;
	if (y_end > env->height)
		y_end = env->height;
	while (y_start < y_end && map[y_start][x] != MAP_WALL)
	{
		sl_check_each_element(env, x, y_start);
		++y_start;
	}
	return (false);
}

void	sl_explode_bomb(t_env *env, t_items *bomb, int x, int y)
{
	bool		is_dead;

	if (bomb->time3 <= BOMB_EXPLODE_TIME)
	{
		is_dead = sl_check_what_is_affected_by_the_explosion(env, bomb, env->map, x / BLOC_LEN, y / BLOC_LEN);
		sl_draw_segments_of_exploding_bomb(env, bomb, x, y);
		if (is_dead)
			env->p1.alive = false;
		++bomb->time3;
	}
	else
	{
		sl_clear_segments_of_exploding_bomb(env, bomb, x, y);
		sl_init_set_bomb(bomb);
		--env->tex.bomb.set_bombs_nbr;
	}
}

void    sl_set_bomb(t_env *env, t_items *bomb)
{
	int			bomb_pos_x;
	int			bomb_pos_y;
	t_states	set_bomb;		

	set_bomb = env->tex.bomb.set_states;
	bomb_pos_x = bomb->pos.x * BLOC_LEN;
	bomb_pos_y = bomb->pos.y * BLOC_LEN;
    if (bomb->time1 <= BOMB_SET_TIME)
    {
        if (bomb->time1 % 320 == 0)
			++bomb->time2;
		if (bomb->time2 % 2 == 0)
			sl_render_bloc_with_xpm(&env->canvas, &set_bomb.one, bomb_pos_x, bomb_pos_y);
		else
		{
			sl_replace_with_green_tile(env, bomb_pos_x, bomb_pos_y);
			sl_render_bloc_with_xpm(&env->canvas, &set_bomb.three, bomb_pos_x, bomb_pos_y);
		}
        ++bomb->time1;
    }
	else
		sl_explode_bomb(env, bomb, bomb_pos_x, bomb_pos_y);
}
