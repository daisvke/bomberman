/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:40:21 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/05 14:41:51 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_init_set_bomb(t_items *bomb, bool draw, int x, int y, int size)
{
	bomb->draw = draw;
	bomb->pos.x = x;
	bomb->pos.y = y;
	bomb->explode_size = size;
	bomb->time1 = 0;
	bomb->time2 = 0;
	bomb->time3 = 0;
}

void	sl_init_sprite(t_sprite *sprite, int x, int y, int speed)
{
	sprite->alive = true;
	sprite->time_death = 0;
	sprite->moves = 0;
	sprite->curr_dir.up = false;
	sprite->curr_dir.down = false;
	sprite->curr_dir.left = false;
	sprite->curr_dir.right = false;
	sprite->curr_state = &sprite->img.down.one;
	sprite->sub_pos.x = 0;
	sprite->sub_pos.y = 0;
	sprite->pos.x = x;
	sprite->pos.y = y;
	sprite->speed = speed;
	sprite->time = 0;
}
