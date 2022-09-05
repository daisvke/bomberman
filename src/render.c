/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 03:31:37 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/20 01:11:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_reveal_exit(t_env *env)
{
	t_pipe		exit;
	t_img		*curr_state;
	t_coord		pos;
	static int	time;

	exit = env->tex.exit_pipe;
	curr_state = NULL;
	if (time <= REVEAL_EXIT_SPEED)
		curr_state = &exit.state0;
	else if (time <= REVEAL_EXIT_SPEED * 2)
		curr_state = &exit.state1;
	else if (time <= REVEAL_EXIT_SPEED * 3)
		curr_state = &exit.state2;
	else if (time <= REVEAL_EXIT_SPEED * 4)
		curr_state = &exit.state3;
	else if (time < REVEAL_EXIT_SPEED * 5)
		curr_state = &exit.state4;
	if (time == REVEAL_EXIT_SPEED * 5)
		curr_state = &exit.state5;
	else
		++time;
	pos = sl_assign_pos(exit.pos.x * BLOC_LEN, exit.pos.y * BLOC_LEN);
	sl_render_bloc_with_xpm(&env->canvas, curr_state, pos, true);
}

void	sl_read_direction_and_animate_sprite(\
	t_env *env, t_sprite_info *info, t_img_patterns *img)
{
	t_coord	pos;
	int		dir;

	dir = info->sprite->curr_dir;
	if (dir & CR_UP)
	{
		pos = sl_assign_pos(0, UP);
		sl_animate_sprite(env, info, &img->up, pos);
	}
	if (dir & CR_DOWN)
	{
		pos = sl_assign_pos(0, DOWN);
		sl_animate_sprite(env, info, &img->down, pos);
	}
	if (dir & CR_LEFT)
	{
		pos = sl_assign_pos(LEFT, 0);
		sl_animate_sprite(env, info, &img->left, pos);
	}
	if (dir & CR_RIGHT)
	{
		pos = sl_assign_pos(RIGHT, 0);
		sl_animate_sprite(env, info, &img->right, pos);
	}
}

void	sl_clear_sprites_last_positions(t_env *env)
{
	t_ennemies	ennemies;
	t_coord		p1_pos;
	t_coord		ennemy_pos;
	int			i;

	p1_pos = sl_assign_pos(env->p1.pos.x * BLOC_LEN, env->p1.pos.y * BLOC_LEN);
	sl_render_green_tile_by_direction(env, env->p1.curr_dir, p1_pos);
	ennemies = env->tex.ennemies;
	i = 0;
	while (i < ennemies.count)
	{
		ennemy_pos.x = ennemies.sprites[i].pos.x * BLOC_LEN;
		ennemy_pos.y = ennemies.sprites[i].pos.y * BLOC_LEN;
		sl_render_green_tile_by_direction(\
			env, ennemies.sprites[i].curr_dir, ennemy_pos);
		++i;
	}
}

void	sl_put_rendered_img_on_canvas(t_env *env)
{
	void	*mlx_img;

	mlx_img = env->canvas.mlx_img;
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, mlx_img, 0, 0);
	sl_put_stage_name(env);
	sl_put_collectible_count_to_window(env);
}

int	sl_render(t_env *env)
{
	sl_clear_sprites_last_positions(env);
	sl_draw_collectibles(env);
	if (env->tex.bomb.collected - START_BOMB == env->tex.bomb.to_collect)
		sl_reveal_exit(env);
	if (env->game_clear)
		sl_exit_when_game_clear(env);
	else
	{
		if (env->map[env->p1.pos.y][env->p1.pos.x] == MAP_ENNEMY)
			env->p1.alive = false;
		sl_render_bombs(env);
		if (env->p1.alive == true)
		{
			sl_render_p1(env);
			sl_render_ennemies(env);
			sl_put_rendered_img_on_canvas(env);
		}
		else
			sl_kill_p1(env);
		sl_put_message_at_start(env);
	}
	return (0);
}
