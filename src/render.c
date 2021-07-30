/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 03:31:37 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/30 15:08:23 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	sl_get_color_from_img(t_img *img, int x, int y)
{
	return ((int)img->addr + (y * img->line_len + x * (img->bpp / 8)));
}

void	sl_img_pixel_put(t_img *img, int x, int y, int color)
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
	while ((y + i) < BLOC_PXL_LEN)
	{
		j = 0;
		while ((x + j) < BLOC_PXL_LEN)
		{
		printf("y: %d, i: %d, j: %d, x: %d, x + j: %d\n", y, i, j, x, x + j);
		//	sl_img_pixel_put(img, j, i, color);
			++j;
		}
		++i;
	}
	return (0);
}

void	sl_render_bloc_with_xpm(t_data *data, t_img *img, int x, int y)
{
	int	color;
	int	i;
	int	j;

	i = 0;
	while (i + y  < BLOC_PXL_LEN)
	{
		j = 0;
		while (j + x < BLOC_PXL_LEN)
		{
			color = sl_get_color_from_img(img, j, i);
			sl_img_pixel_put(img, j, i, color);
			++j;
		}
		++i;
	}
}

void	sl_render_background(t_data *data, t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (data->height / BLOC_PXL_LEN))
	{
		j = 0;
		while (j < (data->width / BLOC_PXL_LEN))
		{
		//	if (data->map[i][j] == '1')
//		printf("mult i: %d j: %d\n",BLOC_PXL_LEN * i, BLOC_PXL_LEN * j);
				sl_render_colored_bloc(img, color, BLOC_PXL_LEN * j, BLOC_PXL_LEN * i);
//		printf(" i: %d, j: %d,\n", i,  j);
			++j;
		}
		++i;
	}
}

int	sl_render(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.mlx_img,data->player.x, data->player.y);
	return (0);
}
