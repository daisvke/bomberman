/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 18:41:30 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/15 16:20:47 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	sl_get_free_slot_in_array(t_env *env, t_items *bombs, t_coord pos)
{
	int	i;

	i = 0;
	while (i < env->tex.bomb.collected)
	{
		if (bombs[i].pos.x == pos.x && bombs[i].pos.y == pos.y)
			break ;
		if (bombs[i].draw == false)
			return (i);
		++i;
	}
	return (NO_AVAILABLE_SLOT);
}

void	sl_handle_keypress_b(t_env *env, int keycode, t_coord pos)
{
	t_items	*set_bombs;
	int		set_bombs_nbr;
	int		collected_bombs;
	int		explode_size;
	int		i;

	set_bombs_nbr = env->tex.bomb.set_bombs_nbr;
	collected_bombs = env->tex.bomb.collected;
	set_bombs = env->tex.bomb.set_bombs; 
	explode_size = env->tex.bomb.explode_size;
    if (keycode == XK_b && set_bombs_nbr < collected_bombs)
	{
		i = sl_get_free_slot_in_array(env, set_bombs, pos);
		if (i != NO_AVAILABLE_SLOT)
		{
			++env->tex.bomb.set_bombs_nbr;
			sl_init_set_bomb(&set_bombs[i], true, pos.x, pos.y, explode_size);
		}
	}
}

bool	sl_found_no_current_direction(t_env *env)
{
	int	dir;
	
	dir = env->p1.curr_dir;
	if ((dir & CR_UP) || (dir & CR_DOWN) || (dir & CR_LEFT) || (dir & CR_RIGHT))
		return (false);
	else
		return (true);
}

int	sl_handle_keypress(int keycode, t_env *env)
{
	int	*dir;

	if (keycode == XK_Escape)
		sl_exit_game(env);
	dir = &env->p1.curr_dir;
	if (sl_found_no_current_direction(env))
	{
		if (keycode == XK_w || keycode == XK_z)
			*dir |= CR_UP;
		if (keycode == XK_s)
			*dir |= CR_DOWN;
		if (keycode == XK_a || keycode == XK_q)
			*dir |= CR_LEFT;
		if (keycode == XK_d)
			*dir |= CR_RIGHT;
	}
	sl_handle_keypress_b(env, keycode, env->p1.pos);
	return (0);
}
