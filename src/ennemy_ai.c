/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_ai.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:23:20 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/05 05:23:26 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_assign_ennemy_curr_dir(t_sprite *sprite, int i)
{
	int	*curr_dir;

	curr_dir = &sprite->curr_dir;
	if (i == 0)
		*curr_dir |= CR_UP;
	if (i == 1)
		*curr_dir |= CR_DOWN;
	if (i == 2)
		*curr_dir |= CR_LEFT;
	if (i == 3)
		*curr_dir |= CR_RIGHT;
}

bool	sl_no_bomb(t_bombs *bombs, t_coord pos)
{
	int		x;
	int		y;
	int		i;

	x = pos.x;
	y = pos.y;
	if (bombs->set_bombs_nbr > 0)
	{
		i = 0;
		while (i < bombs->collected)
		{
			if (bombs->set_bombs[i].draw == true)
				if (x == bombs->set_bombs[i].pos.x)
					if (y == bombs->set_bombs[i].pos.y)
						return (false);
			++i;
		}
	}
	return (true);
}

bool	sl_no_wall(char **map, t_coord pos)
{
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	return (map[y][x] != MAP_WALL);
}

int	sl_keep_direction_if_no_obstacle(\
	t_env *env, char **map, int curr_dir, t_coord pos)
{
	t_coord	coord;
	int		dir;
	t_bombs	*bombs;

	bombs = &env->tex.bomb;
	coord = sl_assign_pos(pos.x, pos.y - 1);
	dir = curr_dir & CR_UP;
	if (dir && sl_no_wall(map, coord) && sl_no_bomb(bombs, coord))
		return (KEEP);
	coord = sl_assign_pos(pos.x, pos.y + 1);
	dir = curr_dir & CR_DOWN;
	if (dir && sl_no_wall(map, coord) && sl_no_bomb(bombs, coord))
		return (KEEP);
	coord = sl_assign_pos(pos.x - 1, pos.y);
	dir = curr_dir & CR_LEFT;
	if (dir && sl_no_wall(map, coord) && sl_no_bomb(bombs, coord))
		return (KEEP);
	coord = sl_assign_pos(pos.x + 1, pos.y);
	dir = curr_dir & CR_RIGHT;
	if (dir && sl_no_wall(map, coord) && sl_no_bomb(bombs, coord))
		return (KEEP);
	return (0);
}

void	sl_read_and_animate_ennemies(t_env *env)
{
	bool			is_alive;
	int				ennemies_count;
	int				i;
	t_sprite_info	info;

	ennemies_count = env->tex.ennemies.count;
	i = 0;
	while (i < ennemies_count)
	{
		is_alive = env->tex.ennemies.sprites[i].alive;
		if (is_alive == true)
		{
			sl_determine_ennemy_direction(env, &env->tex.ennemies.sprites[i]);
			info.sprite = &env->tex.ennemies.sprites[i];
			info.apply_to = ENNEMY;
			sl_read_direction_and_animate_sprite(\
				env, &info, &env->tex.ennemies.img);
		}
		++i;
	}
}
