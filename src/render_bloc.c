/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 20:03:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/03 20:44:19 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	sl_get_color_from_img(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

void	sl_img_pixel_put(t_img *img, int x, int y, int color, bool mask)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	if ((mask && color != GREEN) || !mask)
	{
		while (i >= 0)
		{
			if (img->endian)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

int	sl_render_colored_bloc(t_img *img, int color, t_coord pos)
{
	int		x;
	int		y;
	int		i;
	int		j;

	x = pos.x;
	y = pos.y;
	i = 0;
	while (i < BLOC_LEN)
	{
		j = 0;
		while (j < BLOC_LEN)
		{
			sl_img_pixel_put(img, j + x, i + y, color, false);
			++j;
		}
		++i;
	}
	return (0);
}

void	sl_render_bloc_with_xpm(t_img *img, t_img *xpm_img, t_coord pos, \
	bool mask)
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
			if (color >= 0)
				sl_img_pixel_put(img, j + x, i + y, color, mask);
			++j;
		}
		++i;
	}
}

void	sl_replace_with_green_tile(t_env *env, t_coord pos)
{
	t_img	*bkgd;
	char	**map;
	t_img	*tile_shadow;
	int		x;
	int		y;

	bkgd = &env->canvas;
	map = env->map;
	x = pos.x / BLOC_LEN;
	y = pos.y / BLOC_LEN;
	if (map[y][x] != MAP_WALL)
	{
		if (map[y - 1][x] == MAP_WALL)
		{
			tile_shadow = &env->tex.tiles.tile_shadow;
			sl_render_bloc_with_xpm(bkgd, tile_shadow, pos, false);
		}
		else
			sl_render_colored_bloc(bkgd, GREEN, pos);
	}
}
