/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 19:37:10 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/04 04:18:31 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	sl_put_buffer_bkgd_to_img(t_env *env)
{
	int		**buffer;
	int		color;
	int		i;
	int		j;
	t_coord	pos;

	buffer = env->buffer_bkgd;
	i = 0;
	while (i < env->height * BLOC_LEN)
	{
		j = 0;
		while (j < env->width * BLOC_LEN)
		{
			color = buffer[i][j];
			pos = sl_assign_pos(j, i);
			sl_img_pixel_put(&env->canvas, pos, color, false);
			++j;
		}
		++i;
	}
}
