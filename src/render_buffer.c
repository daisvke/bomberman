/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 19:50:14 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/03 20:43:29 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	sl_render_buffer_with_colored_bloc(int **buffer, int color, t_coord pos)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = pos.x;
	y = pos.y;
	i = 0;
	while (i < BLOC_LEN)
	{
		j = 0;
		while (j < BLOC_LEN)
		{
			buffer[i + y][j + x] = color;
			++j;
		}
		++i;
	}
	return (0);
}

void	sl_render_buffer_bloc_with_xpm(int **buff, t_img *xpm_img, t_coord pos)
{
	int	x;
	int	y;
	int	color;
	int	i;
	int	j;

	x = pos.x;
	y = pos.y;
	i = 0;
	while (i < BLOC_LEN)
	{
		j = 0;
		while (j < BLOC_LEN)
		{
			color = sl_get_color_from_img(xpm_img, j, i);
			buff[i + y][j + x] = color;
			++j;
		}
		++i;
	}
}

void	sl_render_buffer_green_tile(t_env *env, t_coord pos)
{
	t_coord	coord;
	t_img	*tile_shadow;
	int		**buffer;
	char	**map;

	tile_shadow = &env->tex.tile_shadow;
	buffer = env->buffer_bkgd;
	map = env->map;
	if (map[pos.y - 1][pos.x] == MAP_WALL)
	{
		coord = sl_assign_pos(BLOC_LEN * pos.x, BLOC_LEN * pos.y);
		sl_render_buffer_bloc_with_xpm(buffer, tile_shadow, coord);
	}
	else
	{
		coord = sl_assign_pos(BLOC_LEN * pos.x, BLOC_LEN * pos.y);
		sl_render_buffer_with_colored_bloc(buffer, GREEN, coord);
	}
}
