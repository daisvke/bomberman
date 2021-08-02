/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/02 14:12:24 by dtanigaw         ###   ########.fr       */
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
	static int	moves;
	char		**map;
	int			x;
	int			y;

	map = data->map;
	x = data->player.x;
	y = data->player.y;
	if (keycode == XK_w && map[y - 1][x] != WALL)
		--data->player.y;
	if (keycode == XK_s && map[y + 1][x] != WALL)
		++data->player.y;
	if (keycode == XK_a && map[y][x - 1] != WALL)
		--data->player.x;
	if (keycode == XK_d && map[y][x + 1] != WALL)
		++data->player.x;
	if (x != data->player.x || y != data->player.y)
	{
		moves++;
		//on window
		printf("%d\n", moves);
	}
	if (map[data->player.y][data->player.x] == ITEM_BOMB)
	{
		sl_render_colored_bloc(&data->img, GREEN_PIXEL, BLOC_PXL_LEN * data->player.x, BLOC_PXL_LEN * data->player.y);
		map[data->player.y][data->player.x] = '0';
		++data->collected_bombs;
//		printf("collected: %d, to: %d\n", data->collected_bombs, data->bombs_to_collect);
		if (data->collected_bombs == data->bombs_to_collect)
		{
			printf("ALL COLLECTED !\n");
			data->exit.appear = true;
			//exit appears
		}
	}
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

void	sl_init_data(t_data *data)
{
	data->bombs_to_collect = 0;
	data->collected_bombs = 0;
	data->exit.appear = false;
}

void	sl_load_texture(t_data *data, t_img *img, char *path_to_file)
{
	int	width;
	int	height;

	img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, path_to_file, &width, &height);
	if (!img->mlx_img)
		exit(EXIT_FAILURE);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
}

int	main(void)
{
	t_data	data;
	char	*path = "./img/bomberman-white-down-0-24x24.xpm";
	int	w;
	int	h;
	
	sl_init_data(&data);
	sl_parse_map(&data, "map");
//	check_map(data);

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		exit(EXIT_FAILURE);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.width, data.height, \
		"BOMBERMAN");
	if (!data.win_ptr)
	{
		free(data.mlx_ptr);
		exit(EXIT_FAILURE);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, data.width, data.height);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	sl_load_texture(&data, &data.wall, "./img/bomberman-grey-tile-24x24.xpm");
/*
	data.wall.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "./img/bomberman-grey-tile-24x24.xpm", &w, &h);
	if (!data.wall.mlx_img)
		exit(EXIT_FAILURE);
	data.wall.addr = mlx_get_data_addr(data.wall.mlx_img, &data.wall.bpp, &data.wall.line_len, &data.wall.endian);
*/
	data.item_bomb.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "./img/bomberman-item-bomb-24x24.xpm", &w, &h);
	if (!data.item_bomb.mlx_img)
		exit(EXIT_FAILURE);
	data.item_bomb.addr = mlx_get_data_addr(data.item_bomb.mlx_img, &data.item_bomb.bpp, &data.item_bomb.line_len, &data.item_bomb.endian);

	sl_render_background(&data);

	data.player.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, path, &w, &h);
	if (!data.player.mlx_img)
		exit(EXIT_FAILURE);

	mlx_loop_hook(data.mlx_ptr, &sl_render, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, sl_handle_keypress, &data);
	mlx_key_hook(data.win_ptr, &sl_handle_input, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	exit(EXIT_SUCCESS);
}
