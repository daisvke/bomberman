/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 20:00:21 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/04 04:50:18 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_kill_ennemy(t_env *env, t_sprite *ennemy)
{
	t_ennemies	ennemies;
	t_coord		pos;
	int			*time_death;

	ennemies = env->tex.ennemies;
	pos = sl_assign_pos(ennemy->sub_pos.x, ennemy->sub_pos.y);
	time_death = &ennemy->time_death;
	if (*time_death <= ENNEMY_DEATH_TIME)
	{
		sl_render_bloc_with_xpm(&env->canvas, &ennemies.dead, pos, true);
		++ennemy->time_death;
	}
}

t_img	*sl_get_death_state(t_env *env, int time)
{
	t_img	*death_state;

	death_state = NULL;
	if (time <= PLAYER_DEATH_TIME / 4)
		death_state = &env->p1.img.dead.one;
	else if (time <= PLAYER_DEATH_TIME / 3.5)
		death_state = &env->p1.img.dead.two;
	else if (time <= PLAYER_DEATH_TIME / 2.7)
		death_state = &env->p1.img.dead.three;
	else if (time <= PLAYER_DEATH_TIME / 2.3)
		death_state = &env->p1.img.dead.four;
	else if (time <= PLAYER_DEATH_TIME / 2)
		death_state = &env->p1.img.dead.five;
	else if (time <= PLAYER_DEATH_TIME / 1.6)
		death_state = &env->p1.img.dead.six;
	else if (time <= PLAYER_DEATH_TIME / 1.3)
		death_state = &env->p1.img.dead.seven;
	else
		death_state = &env->p1.img.dead.eight;
	return (death_state);
}

void	sl_kill_p1(t_env *env)
{
	t_img		*death_state;
	t_coord		pos;
	static int	time;

	death_state = NULL;
	if (time <= CENTER_MESS_TIME)
	{
		death_state = sl_get_death_state(env, time);
		pos = sl_assign_pos(env->p1.sub_pos.x, env->p1.sub_pos.y);
		sl_render_bloc_with_xpm(&env->canvas, death_state, pos, true);
		mlx_put_image_to_window(\
			env->mlx_ptr, env->win_ptr, env->canvas.mlx_img, 0, 0);
	}
	++time;
	sl_exit_when_game_over(env);
}
