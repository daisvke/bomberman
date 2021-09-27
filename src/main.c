/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/15 16:20:47 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	sl_check_inputs(t_env *env, int argc, char *filename)
{
	char	*file_extension;

	if (argc < 2)
		sl_put_err_code_and_exit_game(env, 3);
	file_extension = ft_strrchr(filename, '.');
	if (!file_extension)
		sl_put_err_code_and_exit_game(env, 4);
	if (ft_strcmp(file_extension, FILE_EXTENSION) != SAME)
		sl_put_err_code_and_exit_game(env, 5);
}

void	sl_handle_events(t_env *env)
{
	void	*win;

	win = env->win_ptr;
	mlx_hook(win, KeyPress, KeyPressMask, &sl_handle_keypress, env);
	mlx_hook(win, ClientMessage, StructureNotifyMask, &sl_exit_game, env);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	
	sl_check_inputs(&env,argc, argv[1]);
	sl_init_all(&env, argv);
	sl_handle_events(&env);
	mlx_loop_hook(env.mlx_ptr, &sl_render, &env);
	mlx_loop(env.mlx_ptr);
}
