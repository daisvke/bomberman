/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/03 06:52:47 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	sl_handle_input(int keysym, t_env *env)
{
	if (keysym == XK_Escape)
	{
		mlx_loop_end(env->mlx_ptr);
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	}
	return (0);
}

/*
int	sl_handle_keypress(int keysym, t_env *env)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	return (0);
}
*/

int	sl_handle_keypress(int keycode, t_env *env)
{
	static int	moves;
	char		**map;
	int			x;
	int			y;

	map = env->map;
	x = env->p1.pos.x;
	y = env->p1.pos.y;
	if (keycode == XK_w && map[y - 1][x] != WALL)
		env->p1.curr_dir.up = true;
	if (keycode == XK_s && map[y + 1][x] != WALL)
		env->p1.curr_dir.down = true;
	if (keycode == XK_a && map[y][x - 1] != WALL)
		env->p1.curr_dir.left = true;
	if (keycode == XK_d && map[y][x + 1] != WALL)
		env->p1.curr_dir.right = true;
	if (x != env->p1.pos.x || y != env->p1.pos.y)
	{
		++moves;
		//on window
		printf("%d\n", moves);
	}


	if (map[env->p1.pos.y][env->p1.pos.x] == ITEM_BOMB)
	{
		sl_render_colored_bloc(&env.bg, GREEN_PXL, BLOC_PXL_LEN * env->p1.pos.x, BLOC_PXL_LEN * env->p1.pos.y);
		map[env->p1.pos.y][env->p1.pos.x] = '0';
		++env->collected_bombs;
//		printf("collected: %d, to: %d\n", env->collected_bombs, env->bombs_to_collect);
		if (env->tex.bomb.collected == env->tex.bomb.to_collect)
		{
			printf("ALL COLLECTED !\n");
			env->exit.appear = true;
			//exit appears
		}
	}
	return (0);
}

void	check_map(t_env *env)
{
	int i, j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%c", env->map[i][j]);
			++j;
		}
		printf("\n");
		++i;
	}
}

void	sl_init_env(t_env *env)
{
	env->bombs_to_collect = 0;
	env->collected_bombs = 0;
	env->exit.appear = false;
	env->down = false;
	env->current = &env->player;
	env->curr_x = 0;
	env->curr_y = 0;
}

void	sl_load_texture(t_env *env, t_img *img, char *path_to_file)
{
	int	width;
	int	height;

	img->mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, path_to_file, &width, &height);
	if (!img->mlx_img)
		exit(EXIT_FAILURE);
	img->addr = mlx_get_env_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
}

void	sl_load_all_textures(t_env *env)
{
	sl_load_texture(&env, env.tex.wall, "./img/bomberman-grey-tile-24x24.xpm");
	sl_load_texture(&env, env.tex.bomb.item_bomb, "./img/bomberman-item-bomb-24x24.xpm", &w, &h);
	sl_load_texture(&env, env.p1.img.up, "./img/bomberman-white-up-0-24x24.xpm");
	sl_load_texture(&env, env.p1.img.up_l, "./img/bomberman-white-up-l-24x24.xpm");
	sl_load_texture(&env, env.p1.img.up_r, "./img/bomberman-white-up-r-24x24.xpm");
	sl_load_texture(&env, env.p1.img.down, "./img/bomberman-white-down-0-24x24.xpm");
	sl_load_texture(&env, env.p1.img.down_l, "./img/bomberman-white-down-l-24x24.xpm");
	sl_load_texture(&env, env.p1.img.down_r, "./img/bomberman-white-down-r-24x24.xpm");
	sl_load_texture(&env, env.p1.img.left, "./img/bomberman-white-left-0-24x24.xpm");
	sl_load_texture(&env, env.p1.img.left_l, "./img/bomberman-white-left-l-24x24.xpm");
	sl_load_texture(&env, env.p1.img.left_r, "./img/bomberman-white-left-r-24x24.xpm");
	sl_load_texture(&env, env.p1.img.right, "./img/bomberman-white-right-0-24x24.xpm");
	sl_load_texture(&env, env.p1.img.right_l, "./img/bomberman-white-right-l-24x24.xpm");
	sl_load_texture(&env, env.p1.img.right_r, "./img/bomberman-white-right-r-24x24.xpm");
}

int	main(void)
{
	t_env	env;
	int	w;
	int	h;
	
	sl_init_env(&env);
	sl_parse_map(&env, "map");

	env.mlx_ptr = mlx_init();
	if (!env.mlx_ptr)
		exit(EXIT_FAILURE);
	env.win_ptr = mlx_new_window(env.mlx_ptr, env.width, env.height, \
		"BOMBERMAN");
	if (!env.win_ptr)
	{
		free(env.mlx_ptr);
		exit(EXIT_FAILURE);
	}
	env.bg.mlx_img = mlx_new_image(env.mlx_ptr, env.width, env.height);
	env.bg.addr = mlx_get_env_addr(env.bg.mlx_img, &env.bg.bpp, &env.bg.line_len, &env.bg.endian);
	
	sl_load_all_textures(&env);
	sl_render_bg(&env);

	mlx_hook(env.win_ptr, 2, 1L << 0, sl_handle_keypress, &env);
	mlx_key_hook(env.win_ptr, &sl_handle_input, &env);
	mlx_loop_hook(env.mlx_ptr, &sl_render, &env);
	mlx_loop(env.mlx_ptr);
	mlx_destroy_display(env.mlx_ptr);
	free(env.mlx_ptr);
	exit(EXIT_SUCCESS);
}
