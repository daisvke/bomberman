/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 19:55:10 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/04 03:30:56 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	sl_render_p1(t_env *env)
{
	t_img_patterns	p1_img;
	t_img			*img;
	t_coord			pos;
	t_sprite_info	info;

	p1_img = env->p1.img;
	info.sprite = &env->p1;
	info.apply_to = PLAYER;
	sl_read_direction_and_animate_sprite(env, &info, &p1_img);
	sl_read_and_animate_ennemies(env);
	img = env->p1.curr_state;
	pos = sl_assign_pos(env->p1.sub_pos.x, env->p1.sub_pos.y);
	sl_render_bloc_with_xpm(&env->canvas, img, pos, true);
}

void	sl_render_bombs(t_env *env)
{
	int	i;

	i = 0;
	if (env->tex.bomb.set_bombs_nbr > 0)
	{
		while (i < env->tex.bomb.collected)
		{
			if (env->tex.bomb.set_bombs[i].draw == true)
				sl_set_bomb(env, &env->tex.bomb.set_bombs[i]);
			++i;
		}
	}
}

void	sl_render_ennemies(t_env *env)
{
	t_ennemies	ennemies;
	t_img		*img;
	t_coord		pos;
	int			i;

	ennemies = env->tex.ennemies;
	i = 0;
	while (i < ennemies.count)
	{
		if (ennemies.sprites[i].alive == true)
		{
			img = env->tex.ennemies.sprites[i].curr_state;
			pos = sl_assign_pos(ennemies.sprites[i].sub_pos.x, \
				ennemies.sprites[i].sub_pos.y);
			sl_render_bloc_with_xpm(&env->canvas, img, pos, true);
		}
		else
			sl_kill_ennemy(env, &env->tex.ennemies.sprites[i]);
		++i;
	}
}

void	sl_draw_collectibles_by_category(t_env *env, t_items *items, \
	t_img *img, int max)
{
	t_coord	pos;
	int		i;
	int		x;
	int		y;

	i = 0;
	while (i < max)
	{
		x = items[i].pos.x * BLOC_LEN;
		y = items[i].pos.y * BLOC_LEN;
		pos = sl_assign_pos(x, y);
		if (items[i].draw == true)
			sl_render_bloc_with_xpm(&env->canvas, img, pos, true);
		else
			sl_replace_with_green_tile(env, pos);
		++i;
	}
}

void	sl_draw_collectibles(t_env *env)
{
	sl_draw_collectibles_by_category(env, env->tex.bomb.item_bombs, \
		&env->tex.bomb.item_bomb, env->tex.bomb.to_collect);
	sl_draw_collectibles_by_category(env, env->tex.fire.items, \
		&env->tex.fire.img, env->tex.fire.to_collect);
	sl_draw_collectibles_by_category(env, env->tex.speed.items, \
		&env->tex.speed.img, env->tex.speed.to_collect);
}
