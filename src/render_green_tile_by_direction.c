/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_green_tile_by_direction.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 19:41:36 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/12 19:47:19 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_render_green_tile_when_going_up(t_env *env, t_img *bkgd, \
	int curr_dir, t_coord map_pos, t_coord pos)
{
	char	**map;
	t_coord	coord;
	t_img	*tile_shadow;
	int		x;
	int		y;

	x = map_pos.x;
	y = map_pos.y;
	map = env->map;
	if ((curr_dir & CR_UP) && map[y - 1][x] != MAP_WALL)
	{
		if (map[y - 2][x] == MAP_WALL)
		{
			coord = sl_assign_pos(pos.x, pos.y - BLOC_LEN);
			tile_shadow = &env->tex.tiles.tile_shadow;
			sl_render_bloc_with_xpm(bkgd, tile_shadow, coord, false);
		}
		else
		{
			coord = sl_assign_pos(pos.x, pos.y - BLOC_LEN);
			sl_render_colored_bloc(bkgd, GREEN, coord);
		}
	}
}

void	sl_render_green_tile_when_going_down(t_env *env, t_img *bkgd, \
	int curr_dir, t_coord map_pos, t_coord pos)
{
	char	**map;
	t_img	*tile_shadow;
	int		x;
	int		y;

	x = map_pos.x;
	y = map_pos.y;
	map = env->map;
	tile_shadow = &env->tex.tiles.tile_shadow;
	if (map[y - 1][x] == MAP_WALL && !(curr_dir & CR_DOWN))
		sl_render_bloc_with_xpm(bkgd, tile_shadow, pos, false);
	else if	(map[y - 1][x] == MAP_WALL && (curr_dir & CR_DOWN))
		sl_render_bloc_with_xpm(bkgd, tile_shadow, pos, false);
	else	
		sl_render_colored_bloc(bkgd, GREEN, pos);
	if ((curr_dir & CR_DOWN) && map[y + 1][x] != MAP_WALL)
	{
		pos = sl_assign_pos(pos.x, pos.y + BLOC_LEN);
		sl_render_colored_bloc(bkgd, GREEN, pos);
	}
}

void	sl_render_green_tile_when_going_left(t_env *env, t_img *bkgd, \
	int curr_dir, t_coord map_pos, t_coord pos)
{
	char	**map;
	t_coord	coord;
	t_img	*tile_shadow;
	int		x;
	int		y;

	x = map_pos.x;
	y = map_pos.y;
	map = env->map;
	if ((curr_dir & CR_LEFT) && map[y][x - 1] != MAP_WALL)
	{
		if (map[y - 1][x - 1] == MAP_WALL)
		{
			tile_shadow = &env->tex.tiles.tile_shadow;
			coord = sl_assign_pos(pos.x - BLOC_LEN, pos.y);
			sl_render_bloc_with_xpm(bkgd, tile_shadow, coord, false);
		}
		else
		{
			coord = sl_assign_pos(pos.x - BLOC_LEN, pos.y);
			sl_render_colored_bloc(bkgd, GREEN, coord);
		}
	}
}

void	sl_render_green_tile_when_going_right(t_env *env, t_img *bkgd, \
	int curr_dir, t_coord map_pos, t_coord pos)
{
	char	**map;
	t_coord	coord;
	t_img	*tile_shadow;
	int		x;
	int		y;

	x = map_pos.x;
	y = map_pos.y;
	map = env->map;
	if ((curr_dir & CR_RIGHT) && map[y][x + 1] != MAP_WALL)
	{
		if (map[y - 1][x + 1] == MAP_WALL)
		{
			tile_shadow = &env->tex.tiles.tile_shadow;
			coord = sl_assign_pos(pos.x + BLOC_LEN, pos.y);
			sl_render_bloc_with_xpm(bkgd, tile_shadow, coord, false);
		}
		else
		{
			coord = sl_assign_pos(pos.x + BLOC_LEN, pos.y);
			sl_render_colored_bloc(bkgd, GREEN, coord);
		}
	}
}

void	sl_render_green_tile_by_direction(t_env *env, int curr_dir, t_coord pos)
{
	t_img	*bkgd;
	t_coord	map_pos;
	int		x;
	int		y;

	bkgd = &env->canvas;
	x = pos.x / BLOC_LEN;
	y = pos.y / BLOC_LEN;
	map_pos = sl_assign_pos(x, y);
	sl_render_green_tile_when_going_up(env, bkgd, curr_dir, map_pos, pos);
	sl_render_green_tile_when_going_down(env, bkgd, curr_dir, map_pos, pos);
	sl_render_green_tile_when_going_left(env, bkgd, curr_dir, map_pos, pos);
	sl_render_green_tile_when_going_right(env, bkgd, curr_dir, map_pos, pos);
}
