/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 05:23:36 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/09 04:47:37 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_put_back_exit_on_map(t_env *env)
{
	char	**map;
	int		x;
	int		y;

	map = env->map;
	x = env->tex.exit_pipe.pos.x;
	y = env->tex.exit_pipe.pos.y;
	map[y][x] = MAP_EXIT;
}

int	sl_is_collectible(char elem_to_check)
{
	int	i;

	i = 0;
	while (MAP_COLLECTIBLES[i])
	{
		if (elem_to_check == MAP_COLLECTIBLES[i])
			return (i + 1);
		++i;
	}
	return (0);
}

void	sl_update_player_pos_on_map(t_env *env, int apply_to, \
	t_sprite *sprite, int x, int y)
{
	char	**map;
	t_coord	old;
	t_coord	new;

	map = env->map;
	old = sl_assign_pos(sprite->pos.x, sprite->pos.y);
	new = sl_assign_pos(sprite->pos.x + x, sprite->pos.y + y);
	if (!(apply_to == ENNEMY && sl_is_collectible(map[old.y][old.x])))
		map[old.y][old.x] = MAP_FLOOR;
	if (apply_to == PLAYER)
		map[sprite->pos.y + y][sprite->pos.x + x] = MAP_PLAYER;
	else if (apply_to == ENNEMY && !sl_is_collectible(map[new.y][new.x]))
		map[new.y][new.x] = MAP_ENNEMY;
	sl_put_back_exit_on_map(env);
}

bool	sl_check_if_bomb_is_there(t_env *env, t_items *bombs, int x, int y)
{
	t_coord	bomb_pos;
	int		i;	

	i = 0;
	while (i < env->tex.bomb.set_bombs_nbr)
	{
		bomb_pos = sl_assign_pos(bombs[i].pos.x, bombs[i].pos.y);
		if (bombs[i].draw == true && x == bomb_pos.x && y == bomb_pos.y)
			return (true);
		++i;
	}
	return (false);
}

void	sl_update_sub_pos(t_sprite *sprite, t_img *img, t_coord delta)
{
	sprite->curr_state = img;
	sprite->sub_pos.x = sprite->pos.x * BLOC_LEN + delta.x;
	sprite->sub_pos.y = sprite->pos.y * BLOC_LEN + delta.y;
}

void	sl_animate_sprite(t_env *env, t_sprite *sprite, int apply_to, t_states *img, t_coord coord) 
{
	char	**map;
	t_coord	pos;
	t_coord	delta_pos;
	int		x;
	int		y;

	map = env->map;
	pos = sl_assign_pos(sprite->pos.x + coord.x, sprite->pos.y + coord.y);
	if (map[pos.y][pos.x] == MAP_WALL || sl_check_if_bomb_is_there(env, env->tex.bomb.set_bombs, pos.x, pos.y))
		coord = sl_assign_pos(0, 0);
	x = coord.x;
	y = coord.y;
	sl_handle_textures_while_moving(env, apply_to, coord);
	if (sprite->time <= sprite->speed)
	{
		delta_pos = sl_assign_pos(x * BLOC_LEN / 3, y * BLOC_LEN / 3);
		sl_update_sub_pos(sprite, &img->two, delta_pos);
	}
	if (sprite->time > sprite->speed)
	{
		delta_pos = sl_assign_pos(x * 2 * BLOC_LEN / 3, y * 2 * BLOC_LEN / 3);
		sl_update_sub_pos(sprite, &img->three, delta_pos);
	}
	if (sprite->time == sprite->speed * 2)
	{
		if (apply_to == PLAYER && (x != 0 || y != 0))
			++env->p1.moves;
		delta_pos = sl_assign_pos(0, 0);
		sl_update_sub_pos(sprite, &img->one, delta_pos);
		sl_update_player_pos_on_map(env, apply_to, sprite, x, y);
		sprite->pos = sl_assign_pos(sprite->pos.x + x, sprite->pos.y + y);
		sprite->sub_pos.x = sprite->pos.x * BLOC_LEN;
		sprite->sub_pos.y = sprite->pos.y * BLOC_LEN;
		if (apply_to != ENNEMY)
			sprite->curr_dir = 0;
		sprite->time = 0;
	}
	else
		++sprite->time;
}
