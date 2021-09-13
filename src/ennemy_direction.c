/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 03:32:01 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/13 03:59:58 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

bool	sl_determine_ennemy_direction_up(t_env *env, t_sprite *sprite, \
	t_coord pos, int len_array[])
{
	char	**map;

	map = env->map;
	while (pos.y >= 0 && map[pos.y][pos.x] != MAP_WALL)
	{
		if (map[pos.y][pos.x] == MAP_PLAYER)
		{
			sprite->curr_dir |= CR_UP;
			return (FOUND_PLAYER);
		}
		++len_array[UP_LEN];
		--pos.y;
	}
	return (0);
}

bool	sl_determine_ennemy_direction_down(t_env *env, t_sprite *sprite, \
	t_coord pos, int len_array[])
{
	char	**map;

	map = env->map;
	while (pos.y < env->height && map[pos.y][pos.x] != MAP_WALL)
	{
		if (map[pos.y][pos.x] == MAP_PLAYER)
		{
			sprite->curr_dir |= CR_DOWN;
			return (FOUND_PLAYER);
		}
		++len_array[DOWN_LEN];
		++pos.y;
	}
	return (0);
}

bool	sl_determine_ennemy_direction_left(t_env *env, t_sprite *sprite, \
	t_coord pos, int len_array[])
{
	char	**map;

	map = env->map;
	while (pos.x >= 0 && map[pos.y][pos.x] != MAP_WALL)
	{
		if (map[pos.y][pos.x] == MAP_PLAYER)
		{
			sprite->curr_dir |= CR_LEFT;
			return (FOUND_PLAYER);
		}
		++len_array[LEFT_LEN];
		--pos.x;
	}
	return (0);
}

bool	sl_determine_ennemy_direction_right(t_env *env, t_sprite *sprite, \
	t_coord pos, int len_array[])
{
	char	**map;

	map = env->map;
	while (pos.x < env->width && map[pos.y][pos.x] != MAP_WALL)
	{
		if (map[pos.y][pos.x] == MAP_PLAYER)
		{
			sprite->curr_dir |= CR_RIGHT;
			return (FOUND_PLAYER);
		}
		++len_array[RIGHT_LEN];
		++pos.x;
	}
	return (0);
}

void	sl_determine_ennemy_direction(t_env *env, t_sprite *sprite)
{
	char	**map;
	t_coord	pos;
	t_coord	bomb_pos;
	int		len_array[4];
	int		keep;

	map = env->map;
	pos = sl_assign_pos(sprite->pos.x, sprite->pos.y);
	bomb_pos = env->tex.bomb.pos;
	keep = sl_keep_direction_if_no_wall(map, bomb_pos, sprite->curr_dir, pos);
	if (keep == true)
		return ;
	sprite->curr_dir = 0;
	sl_init_array(len_array, 4);
	if (sl_determine_ennemy_direction_up(env, sprite, pos, len_array) \
		|| sl_determine_ennemy_direction_down(env, sprite, pos, len_array) \
		|| sl_determine_ennemy_direction_left(env, sprite, pos, len_array) \
		|| sl_determine_ennemy_direction_right(env, sprite, pos, len_array) \
		== FOUND_PLAYER)
		return ;
	sl_get_max_len(sprite, len_array);
}
