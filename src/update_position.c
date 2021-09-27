/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:34:33 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/12 15:39:09 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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

void	sl_update_sub_pos(t_sprite *sprite, t_img *img, t_coord delta)
{
	sprite->curr_state = img;
	sprite->sub_pos.x = sprite->pos.x * BLOC_LEN + delta.x;
	sprite->sub_pos.y = sprite->pos.y * BLOC_LEN + delta.y;
}

void	sl_update_sub_pos_state_0(t_sprite *sprite, t_states *img, t_coord pos)
{
	t_coord	delta_pos;
	int		x;
	int		y;

	x = pos.x;
	y = pos.y;
	delta_pos = sl_assign_pos(x * BLOC_LEN / 3, y * BLOC_LEN / 3);
	sl_update_sub_pos(sprite, &img->two, delta_pos);
}

void	sl_update_sub_pos_state_1(t_sprite *sprite, t_states *img, t_coord pos)
{
	t_coord	delta_pos;
	int		x;
	int		y;

	x = pos.x;
	y = pos.y;
	delta_pos = sl_assign_pos(x * 2 * BLOC_LEN / 3, y * 2 * BLOC_LEN / 3);
	sl_update_sub_pos(sprite, &img->three, delta_pos);
}

void	sl_update_sub_pos_state_2(t_env *env, t_sprite *sprite, int apply_to, \
	t_states *img, t_coord coord)
{
	t_coord	delta_pos;
	int		x;
	int		y;

	x = coord.x;
	y = coord.y;
	delta_pos = sl_assign_pos(0, 0);
	sl_update_sub_pos(sprite, &img->one, delta_pos);
	sl_update_player_pos_on_map(env, apply_to, sprite, x, y);
	sprite->pos = sl_assign_pos(sprite->pos.x + x, sprite->pos.y + y);
	sprite->sub_pos.x = sprite->pos.x * BLOC_LEN;
	sprite->sub_pos.y = sprite->pos.y * BLOC_LEN;
}
