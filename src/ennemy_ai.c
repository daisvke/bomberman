/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_ai.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:23:20 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/04 03:34:27 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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

bool	sl_no_bomb(t_coord bomb, t_coord pos)
{
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	return (x != bomb.x && y != bomb.y);
}

bool	sl_no_wall(char **map, t_coord pos)
{
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	return (map[y][x] != MAP_WALL);
}

int	sl_keep_direction_if_no_wall(char **map, t_coord bomb, int curr_dir, \
	t_coord pos)
{
	t_coord	coord;
	int		dir;

	coord = sl_assign_pos(pos.x, pos.y - 1);
	dir = curr_dir & CR_UP;
	if (dir && sl_no_wall(map, coord) && sl_no_bomb(bomb, coord))
		return (KEEP);
	coord = sl_assign_pos(pos.x, pos.y + 1);
	dir = curr_dir & CR_DOWN;
	if (dir && sl_no_wall(map, coord) && sl_no_bomb(bomb, coord))
		return (KEEP);
	coord = sl_assign_pos(pos.x - 1, pos.y);
	dir = curr_dir & CR_LEFT;
	if (dir && sl_no_wall(map, coord) && sl_no_bomb(bomb, coord))
		return (KEEP);
	coord = sl_assign_pos(pos.x + 1, pos.y);
	dir = curr_dir & CR_RIGHT;
	if (dir && sl_no_wall(map, coord) && sl_no_bomb(bomb, coord))
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
			sl_read_direction_and_animate_sprite( \
				env, &info, &env->tex.ennemies.img);
		}
		++i;
	}
}
