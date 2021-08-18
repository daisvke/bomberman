/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_interactions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:03:39 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/18 03:00:31 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_collect_bomb(t_env *env, char **map, int x, int y)
{
	if (map[y][x] == MAP_ITEM_BOMB)
	{
		sl_render_colored_bloc(env->buffer, GREEN_PXL, BLOC_LEN * x, BLOC_LEN * y);
		map[y][x] = MAP_FLOOR;
		++env->tex.bomb.collected;
		if (env->tex.bomb.collected == env->tex.bomb.to_collect)
			env->tex.exit_pipe.appear = true;
	}
}

void	sl_exit_when_game_clear(char **map, t_pipe *exit_pipe, int x, int y)
{
	if (map[y][x] == MAP_EXIT && exit_pipe->appear == true)
	{
		printf("GAME CLEAR\n");
		exit(EXIT_SUCCESS);
	}
}

void	sl_handle_textures_while_moving(t_env *env, int apply_to, int delta_x, \
	int delta_y)
{
	int	x;
	int	y;

	if (apply_to == PLAYER)
	{
		x = env->p1.pos.x + delta_x;
		y = env->p1.pos.y + delta_y;
		sl_collect_bomb(env, env->map, x, y);
		sl_exit_when_game_clear(env->map, &env->tex.exit_pipe, x, y);
	}
}
