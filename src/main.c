/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/28 03:55:51 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
/*
int	sl_handle_input(int keysym, t_env *env)
{
	if (keysym == XK_Escape)
		sl_exit_game(env, NULL);
	return (0);
}
*/

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

int	sl_get_free_slot_in_array(t_env *env, t_items *bombs, int x, int y)
{
	int	i;

	i = 0;
	while (i < env->tex.bomb.collected)
	{
		if (bombs[i].pos.x == x && bombs[i].pos.y == y)
			break ;
		if (bombs[i].draw == false)
			return (i);
		++i;
	}
	return (-1);
}

int	sl_handle_keypress(int keycode, t_env *env)
{
	int	x;
	int	y;
	int	i;

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
    if (keycode == XK_b && env->tex.bomb.set_bombs_nbr < env->tex.bomb.collected)
	{
		i = sl_get_free_slot_in_array(env, env->tex.bomb.set_bombs, x, y);
		if (i != -1)
		{
        	++env->tex.bomb.set_bombs_nbr;
			env->tex.bomb.set_bombs[i].pos.x = x;
			env->tex.bomb.set_bombs[i].pos.y = y;
			env->tex.bomb.set_bombs[i].draw = true;
			env->tex.bomb.set_bombs[i].explode_size = env->tex.bomb.explode_size;
		}
	}
	return (0);
}

int	sl_handle_keyrelease(int keycode, t_env *env)
{
	int			x;
	int			y;

	x = env->p1.pos.x;
	y = env->p1.pos.y;
	if (keycode == XK_w || keycode == XK_z)
		env->p1.curr_dir.up = false;
	if (keycode == XK_s)
		env->p1.curr_dir.down = false;
	if (keycode == XK_a || keycode == XK_q)
		env->p1.curr_dir.left = false;
	if (keycode == XK_d || keycode == XK_d)
		env->p1.curr_dir.right = false;
	return (0);
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
	env.canvas.mlx_img = mlx_new_image(env.mlx_ptr, width, height);
	env.canvas.addr = mlx_get_data_addr(env.canvas.mlx_img, &env.canvas.bpp, &env.canvas.line_len, &env.canvas.endian);
	
	sl_render_background(&env);
	sl_put_buffer_bkgd_to_img(&env);

	mlx_hook(env.win_ptr, 2, 1L << 0, sl_handle_keypress, &env);
//	mlx_hook(env.win_ptr, 3, 1L << 1, sl_handle_keyrelease, &env);
	mlx_hook(env.win_ptr, 33, 1L << 17, sl_exit_game, &env);
//	mlx_key_hook(env.win_ptr, &sl_handle_input, &env);
	mlx_loop_hook(env.mlx_ptr, &sl_render, &env);
	mlx_loop(env.mlx_ptr);
}
