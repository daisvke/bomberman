/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/20 03:04:35 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	sl_handle_input(int keysym, t_env *env)
{
	if (keysym == XK_Escape)
		sl_exit_game(env, NULL);
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
	char		**map;
	int			x;
	int			y;

	map = env->map;
	x = env->p1.pos.x;
	y = env->p1.pos.y;
	if (keycode == XK_Escape)
		sl_exit_game(env, NULL);
	if (keycode == XK_w || keycode == XK_z)
		env->p1.curr_dir.up = true;
	if (keycode == XK_s)
		env->p1.curr_dir.down = true;
	if (keycode == XK_a || keycode == XK_q)
		env->p1.curr_dir.left = true;
	if (keycode == XK_d || keycode == XK_d)
		env->p1.curr_dir.right = true;
    if (keycode == XK_b && !env->tex.bomb.set_bomb)
	{
        env->tex.bomb.set_bomb = true;
		env->tex.bomb.pos.x = x;
		env->tex.bomb.pos.y = y;
	}
	return (0);
}

void	check_map(t_env *env)
{
	int i, j;

	i = 0;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
		{
			printf("%c", env->map[i][j]);
			++j;
		}
		printf("\n");
		++i;
	}
	printf("\n");
}

void	sl_init_buffers(t_env *env)
{
	int	i;

	env->buffer = malloc(sizeof(int *) * env->height * BLOC_LEN);
	if (!env->buffer)
		sl_exit_game(env, "Error: memory allocation for buffer failed");
	i = 0;
	while (i < env->height * BLOC_LEN)
	{
		env->buffer[i] = malloc(sizeof(int) * env->width * BLOC_LEN);
		++i;
	}
	env->buffer_bkgd = malloc(sizeof(int *) * env->height * BLOC_LEN);
	if (!env->buffer_bkgd)
		sl_exit_game(env, "Error: memory allocation for buffer failed");
	i = 0;
	while (i < env->height * BLOC_LEN)
	{
		env->buffer_bkgd[i] = malloc(sizeof(int) * env->width * BLOC_LEN);
		++i;
	}
}

void	sl_init_sprite(t_sprite *sprite, int x, int y)
{
	sprite->alive = true;
	sprite->moves = 0;
	sprite->curr_dir.up = false;
	sprite->curr_dir.down = false;
	sprite->curr_dir.left = false;
	sprite->curr_dir.right = false;
	sprite->curr_state = &sprite->img.down.one;
	sprite->sub_pos.x = 0;
	sprite->sub_pos.y = 0;
	sprite->pos.x = x;
	sprite->pos.y = y;
	sprite->time = 0;
}

void	sl_init_env(t_env *env)
{
	env->width = 0;
	env->height = 0;
	env->map = NULL;
	env->tex.bomb.to_collect = 0;
	env->tex.bomb.collected = 0;
    env->tex.bomb.set_bomb = false;
	env->tex.exit_pipe.appear = false;
	env->tex.ennemies.count = 0;
	sl_init_sprite(&env->p1, 0, 0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned)s1[i] - (unsigned)s2[i]);
}

void	sl_check_input(int argc, char *filename)
{
	char	*file_extension;

	if (argc < 2)
		exit(EXIT_FAILURE);
	file_extension = ft_strrchr(filename, '.');
	if (!file_extension)
		exit(EXIT_FAILURE);
	if (ft_strcmp(file_extension, FILE_EXTENSION) != 0)
		exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	int		width;
	int		height;

	sl_check_input(argc, argv[1]);
	sl_init_env(&env);
	sl_parse_map(&env, argv[1]);
	sl_init_buffers(&env);
	width = env.width * BLOC_LEN;
	height = env.height * BLOC_LEN;

	env.mlx_ptr = mlx_init();
	if (!env.mlx_ptr)
		exit(EXIT_FAILURE);
	env.win_ptr = mlx_new_window(env.mlx_ptr, width, height, \
		"Bomberman");
	if (!env.win_ptr)
	{
		free(env.mlx_ptr);
		exit(EXIT_FAILURE);
	}
	sl_load_all_textures(&env);
	env.bkgd.mlx_img = mlx_new_image(env.mlx_ptr, width, height);
	env.bkgd.addr = mlx_get_data_addr(env.bkgd.mlx_img, &env.bkgd.bpp, &env.bkgd.line_len, &env.bkgd.endian);
	
	sl_render_background(&env);

	mlx_hook(env.win_ptr, 2, 1L << 0, sl_handle_keypress, &env);
	mlx_hook(env.win_ptr, 33, 1L << 17, sl_exit_game, &env);
//	mlx_key_hook(env.win_ptr, &sl_handle_input, &env);
	mlx_loop_hook(env.mlx_ptr, &sl_render, &env);
	mlx_loop(env.mlx_ptr);
}
