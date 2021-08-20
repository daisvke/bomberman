/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 05:23:36 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/20 03:02:02 by dtanigaw         ###   ########.fr       */
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

void	sl_update_player_pos_on_map(t_env *env, int apply_to, \
	t_sprite *sprite, int x, int y)
{
	char	**map;
	int		old_x;
	int		old_y;
	int		new_x;
	int		new_y;

	map = env->map;
	old_x = sprite->pos.x;
	old_y = sprite->pos.y;
	new_x = sprite->pos.x + x;
	new_y = sprite->pos.y + y;
	if (!(apply_to == ENNEMY && (map[old_y][old_x] == MAP_ITEM_BOMB)))
		map[old_y][old_x] = MAP_FLOOR;
	if (apply_to == PLAYER)
		map[sprite->pos.y + y][sprite->pos.x + x] = MAP_PLAYER;
	else if (apply_to == ENNEMY && map[new_y][new_x] != MAP_ITEM_BOMB)
		map[new_y][new_x] = MAP_ENNEMY;
	sl_put_back_exit_on_map(env);
}

void	sl_animate_sprite(t_env *env, t_sprite *sprite, int apply_to, t_states *img, bool *state, int x, int y)
{
	char		**map;
	int			pos_x;
	int			pos_y;
	t_coord		bomb_pos;
	int		old_x;
	int		old_y;
	int		new_x;
	int		new_y;

	old_x = sprite->pos.x;
	old_y = sprite->pos.y;
	new_x = sprite->pos.x + x;
	new_y = sprite->pos.y + y;

	map = env->map;
	pos_x = sprite->pos.x + x;
	pos_y = sprite->pos.y + y;
	bomb_pos.x = env->tex.bomb.pos.x;
	bomb_pos.y = env->tex.bomb.pos.y;
	if (map[pos_y][pos_x] == MAP_WALL || (env->tex.bomb.set_bomb == true && (bomb_pos.x == pos_x && bomb_pos.y == pos_y)))
	{
		x = 0;
		y = 0;
	}
	sl_handle_textures_while_moving(env, apply_to, x, y);
	if (sprite->time <= 60)
	{
		sprite->curr_state = &img->two;
		sprite->sub_pos.x = sprite->pos.x * BLOC_LEN + x * (BLOC_LEN / 3);
		sprite->sub_pos.y = sprite->pos.y * BLOC_LEN + y * (BLOC_LEN / 3);
	}
	if (sprite->time > 60)
	{
		sprite->curr_state = &img->three;
		sprite->sub_pos.x = sprite->pos.x * BLOC_LEN + x * (2 * (BLOC_LEN / 3));
		sprite->sub_pos.y = sprite->pos.y * BLOC_LEN + y * (2 * (BLOC_LEN / 3));
	}
	if (sprite->time == 120)
	{
		if (apply_to == PLAYER && (x != 0 || y != 0))
			++env->p1.moves;
		sprite->curr_state = &img->one;
		sl_update_player_pos_on_map(env, apply_to, sprite, x, y);
		sprite->pos.x += x;
		sprite->pos.y += y;
		sprite->sub_pos.x = sprite->pos.x * BLOC_LEN;
		sprite->sub_pos.y = sprite->pos.y * BLOC_LEN;
		if (apply_to != ENNEMY)
			*state = false;
		sprite->time = 0;
	}
	else
		++sprite->time;
}
