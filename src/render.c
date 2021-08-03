/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 03:31:37 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/03 16:03:45 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	sl_get_color_from_img(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

void	sl_img_pixel_put(t_img *img, int x , int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int		sl_render_colored_bloc(t_img *img, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < BLOC_PXL_LEN)
	{
		j = 0;
		while (j < BLOC_PXL_LEN)
		{
//		printf("y: %d, i: %d, j: %d, x: %d, x + j: %d\n", y, i, j, x, x + j);
			sl_img_pixel_put(img, j + x, i + y, color);
			++j;
		}
		++i;
	}
	return (0);
}

void	sl_render_bloc_with_xpm(t_img *img, t_img *xpm_img, int x, int y)
{
	unsigned int	color;
	int	i;
	int	j;

	i = 0;
	while (i < BLOC_PXL_LEN)
	{
		j = 0;
		while (j < BLOC_PXL_LEN)
		{
			color = sl_get_color_from_img(xpm_img, j, i);
			sl_img_pixel_put(img, j + x, i + y, color);
			++j;
		}
		++i;
	}
}

void	sl_render_background(t_env *env)
{
	char	**map;
	int		i;
	int		j;

	map = env->map;
	i = 0;
	while (i < (env->height / BLOC_PXL_LEN))
	{
		j = 0;
		while (j < (env->width / BLOC_PXL_LEN))
		{
			if (map[i][j] != '1')
				sl_render_colored_bloc(&env->img, GREEN_PIXEL, BLOC_PXL_LEN * j, BLOC_PXL_LEN * i);
			else
				sl_render_bloc_with_xpm(&env->img, &env->wall,  BLOC_PXL_LEN * j,  BLOC_PXL_LEN * i);
			if (map[i][j] == '2' && map[env->player.y][env->player.x] != ITEM_BOMB)
				sl_render_bloc_with_xpm(&env->img, &env->item_bomb,  BLOC_PXL_LEN * j,  BLOC_PXL_LEN * i);
			if (map[i][j] == '3' && env->exit.appear == true)
				sl_render_bloc_with_xpm(&env->img, &env->exit.img,  BLOC_PXL_LEN * j,  BLOC_PXL_LEN * i);
			++j;
		}
		++i;
	}
}

int	sl_move(t_env *env)
{
	static int	i;
	
	if (i <= 1600)
	{
		env->current = &env->player2;
		env->curr_x = env->player.x * BLOC_PXL_LEN;
		env->curr_y = (env->player.y * BLOC_PXL_LEN) + (BLOC_PXL_LEN / 3);
	}
	if (i > 1600 && i <= 3200)
	{
		env->current = &env->player3;
		env->curr_x = env->player.x * BLOC_PXL_LEN;
		env->curr_y = (env->player.y * BLOC_PXL_LEN) + (2 * (BLOC_PXL_LEN / 3));
	}
	if (i == 4200)
	{
		env->current = &env->player;
		env->curr_x = env->player.x * BLOC_PXL_LEN;
		env->curr_y = (env->player.y * BLOC_PXL_LEN) + BLOC_PXL_LEN;
		++env->player.y;
		env->down = false;
		i = 0;
	}
	else
	{

		++i;
	}
	return (0);
}

int	sl_render(t_env *env)
{
	t_img	*img;
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img.mlx_img, 0, 0);
	if (env->down)
		sl_move(env);
	img = env->current;
	if (img->mlx_img)
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, img->mlx_img, env->curr_x, env->curr_y);
	return (0);
}
