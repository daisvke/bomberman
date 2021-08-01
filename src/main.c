/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/01 05:13:08 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	sl_handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_loop_end(data->mlx_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	}
	return (0);
}

/*
int	sl_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}
*/

int	sl_handle_keypress(int keycode, t_data *data)
{
	if (keycode == XK_w && data->map[(data->player.y + 1) / BLOC_PXL_LEN][data->player.x / BLOC_PXL_LEN] != '1')
		--data->player.y;
	if (keycode == XK_s)
		++data->player.y;
	if (keycode == XK_a)
		--data->player.x;
	if (keycode == XK_d)
		++data->player.x;
	return (0);
}

void	check_map(t_data *data)
{
	int i, j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%c", data->map[i][j]);
			++j;
		}
		printf("\n");
		++i;
	}
}

int	main(void)
{
	t_data	data;
	char	*path = "./img/bomberman-white-down-0-24x24.xpm";
	int	w;
	int	h;

	sl_parse_map(&data, "map");
//	check_map(data);


	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		exit(EXIT_FAILURE);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, \
		"My first window");
	if (!data.win_ptr)
	{
		free(data.mlx_ptr);
		exit(EXIT_FAILURE);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, data.width, data.height);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	
	data.wall.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "./img/bomberman-grey-tile-24x24.xpm", &w, &h);
	if (!data.wall.mlx_img)
		exit(EXIT_FAILURE);
	data.wall.addr = mlx_get_data_addr(data.wall.mlx_img, &data.wall.bpp, &data.wall.line_len, &data.wall.endian);

	sl_render_background(&data);

	data.player.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, path, &w, &h);
	if (!data.player.mlx_img)
		exit(EXIT_FAILURE);
//	data.player.x = 100;
//	data.player.y = 100;

	mlx_loop_hook(data.mlx_ptr, &sl_render, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, sl_handle_keypress, &data);
	mlx_key_hook(data.win_ptr, &sl_handle_input, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	exit(EXIT_SUCCESS);
}
