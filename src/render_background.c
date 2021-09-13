/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 19:37:10 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/13 03:42:15 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_render_background_green_tile(t_env *env, int x, int y)
{
	t_coord	pos;

	pos = sl_assign_pos(x, y);
	sl_render_buffer_green_tile(env, pos);
}

void	sl_render_background_wall(t_env *env, int x, int y)
{
	t_coord	pos;
	t_img	*wall;

	pos = sl_assign_pos(BLOC_LEN * x, BLOC_LEN * y);
	wall = &env->tex.wall;
	sl_render_buffer_bloc_with_xpm(env->buffer_bkgd, wall, pos);
}

void	sl_render_background(t_env *env)
{
	char	**map;
	int		i;
	int		j;

	map = env->map;
	i = 0;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
		{
			if (map[i][j] != MAP_WALL)
				sl_render_background_green_tile(env, j, i);
			else
				sl_render_background_wall(env, j, i);
			++j;
		}
		++i;
	}
}
