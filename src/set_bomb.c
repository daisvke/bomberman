/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 20:21:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/23 02:29:30 by dtanigaw         ###   ########.fr       */
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

	p1_x = env->p1.pos.x;
	p1_y = env->p1.pos.y; 
	x_start = x - 2;
	if (x_start < 0)
		x_start = 0;
	x_end = x + 2;
	if (x_start > env->width)
		x_end = env->width;
	y_start = y - 2;
	if (y_start < 0)
		y_start = 0;
	y_end = y + 2;
	if (y_start > env->width)
		y_end = env->width;
	while (x_start < x_end)
	{
		if (map[y][x_start] == MAP_PLAYER)
			return (true);
		if (map[y][x_start] == MAP_ENNEMY)
			sl_find_which_ennemy_is_dead(env, x_start, y);
		if (map[y][x_start] == MAP_ITEM_BOMB)
		{
			sl_render_buffer_green_tile(env, x_start, y);
			map[y][x_start] = MAP_FLOOR;
		}
		++x_start;
	}
	while (y_start < y_end)
	{
		if (map[y_start][x] == MAP_PLAYER)
			return (true);
		if (map[y_start][x] == MAP_ITEM_BOMB)
		{
			sl_render_buffer_green_tile(env, x, y_start);
			map[y_start][x] = MAP_FLOOR;
		}
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
		{
			sl_render_bloc_with_xpm(&env->bkgd, &set_bomb.one, bomb_pos_x, bomb_pos_y);
		//	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, set_bomb.one.mlx_img, bomb_pos_x, bomb_pos_y);
		//	env->tex.bomb.curr_state = &set_bomb.one;
		}
		else
		{
			sl_render_bloc_with_xpm(&env->bkgd, &set_bomb.three, bomb_pos_x, bomb_pos_y);
		//	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, set_bomb.three.mlx_img, bomb_pos_x, bomb_pos_y);
		//	env->tex.bomb.curr_state = &set_bomb.three;
		}
        ++i;
    }
	if (i > 1280)
		sl_explode_bomb(env, bomb_pos_x, bomb_pos_y, &i, &j);
}
