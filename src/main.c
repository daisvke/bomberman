/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/17 14:26:14 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	ft_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	render_rect(t_data *data, t_rect rect)
{
	int	i;
	int	j;

	if (!data->win_ptr)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	render(t_data *data)
{
	t_rect	rect;

	rect.x = WINDOW_WIDTH - 100;
	rect.y = WINDOW_HEIGHT - 100;
	rect.width = 100;
	rect.height = 100;
	rect.color = GREEN_PIXEL;
	render_rect(data, rect);
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
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_key_hook(data.win_ptr, &ft_handle_input, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	exit(EXIT_SUCCESS);
}
