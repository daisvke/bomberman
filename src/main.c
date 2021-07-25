/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/25 04:48:58 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_loop_end(data->mlx_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	}
	return (0);
}

int	ft_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

void	ft_img_pixel_put(t_img *img, int x, int y, int color)
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

int	ft_render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			ft_img_pixel_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	ft_render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			ft_img_pixel_put(img, j++, i, color);
		++i;
	}
}
/*
void	ft_render_player(t_img *img, int x, int y)
{
	int	i;
	int	j;

	while (i < y)
	{
		j = 0;
		while (j < x)
			ft_img_pixel_put(img, j++, i, color);
		++i;
	}
}
*/
int	ft_render(t_data *data)
{
	t_rect	rect;
	char	*path = "./batman.xpm";
	int	w;
	int	h;
	ft_render_background(&data->img, WHITE_PIXEL);
	data->player.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, path, &w, &h);
	if (!data->player.mlx_img)
		exit(EXIT_FAILURE);
//	ft_render_player(&data->img, 100, 10);
	data->width = w;
	data->height = h;
	rect.x = WINDOW_WIDTH - 100;
	rect.y = WINDOW_HEIGHT - 100;
	rect.width = 100;
	rect.height = 100;
	rect.color = GREEN_PIXEL;
	ft_render_rect(&data->img, rect);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.mlx_img, 100, 10);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		exit(EXIT_FAILURE);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, \
		"My first window");
	if (!data.win_ptr)
	{
		free(data.win_ptr);
		exit(EXIT_FAILURE);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &ft_render, &data);
	mlx_key_hook(data.win_ptr, &ft_handle_input, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	exit(EXIT_SUCCESS);
}
