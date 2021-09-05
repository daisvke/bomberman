/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/05 14:50:25 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_check_inputs(t_env *env, int argc, char *filename)
{
	char	*file_extension;

	if (argc < 2)
		sl_set_err_code_and_exit_game(env, 3);
	file_extension = ft_strrchr(filename, '.');
	if (!file_extension)
		sl_set_err_code_and_exit_game(env, 4);
	if (ft_strcmp(file_extension, FILE_EXTENSION) != SAME)
		sl_set_err_code_and_exit_game(env, 5);
}

void	sl_init_mlx(t_env *env, int width, int height)
{
	char	*title;

	env->mlx_ptr = mlx_init();
	if (!env->mlx_ptr)
		sl_set_err_code_and_exit_game(env, 1);
	title = "minibomberman";
	env->win_ptr = mlx_new_window(env->mlx_ptr, width, height, title);
	if (!env->win_ptr)
		sl_set_err_code_and_exit_game(env, 2);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	
	sl_check_inputs(&env,argc, argv[1]);
	sl_init_all(&env, argv);
	mlx_hook(env.win_ptr, 2, 1L << 0, sl_handle_keypress, &env);
//	mlx_hook(env.win_ptr, 3, 1L << 1, sl_handle_keyrelease, &env);
	mlx_hook(env.win_ptr, 33, 1L << 17, sl_exit_game, &env);
	mlx_loop_hook(env.mlx_ptr, &sl_render, &env);
	mlx_loop(env.mlx_ptr);
}
