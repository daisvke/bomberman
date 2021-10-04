/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:51:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/03 20:56:53 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	sl_exit_game(t_env *env)
{
	if (env->map)
		sl_free_map(env, env->map);
	if (env->buffer_bkgd)
		sl_free_buffer(env->buffer_bkgd, env->height * BLOC_LEN);
	if (env->canvas.mlx_img)
		mlx_destroy_image(env->mlx_ptr, env->canvas.mlx_img);
	if (env->win_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	if (env->mlx_ptr)
	{
		mlx_loop_end(env->mlx_ptr);
		mlx_destroy_display(env->mlx_ptr);
		sl_free(env->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}

void	sl_put_err_code_and_exit_if_map_is_incomplete(t_env *env, int i)
{
	char	*err_message;

	sl_free_map_when_not_complete(env->map, i);
	err_message = NULL;
	sl_put_str_to_terminal("\nError code: 20");
	err_message = sl_get_err_message_from_err_code(20);
	sl_put_colored_str_to_terminal(err_message, STR_RED);
	exit(EXIT_SUCCESS);
}

void	sl_put_err_code_and_exit_game(t_env *env, int err_code)
{
	char	*err_message;

	err_message = NULL;
	sl_put_str_to_terminal("\nError code: ");
	sl_put_nbr_to_terminal(err_code);
	err_message = sl_get_err_message_from_err_code(err_code);
	sl_put_colored_str_to_terminal(err_message, STR_RED);
	sl_exit_game(env);
}

void	sl_exit_when_game_clear(t_env *env)
{
	static int	time;

	if (time <= CENTER_MESS_TIME * 2)
		sl_put_centered_message_to_window(env, "GAME CLEAR !");
	else
	{
		sl_put_str_to_terminal("\n");
		sl_put_colored_str_to_terminal("GAME CLEAR !", STR_CYAN);
		sl_put_steps_on_terminal(env);
		sl_exit_game(env);
	}
	++time;
}

void	sl_exit_when_game_over(t_env *env)
{
	static int	time;
	int			collected;
	int			to_collect;

	if (time <= CENTER_MESS_TIME)
		sl_put_centered_message_to_window(env, "GAME OVER !");
	else
	{
		sl_put_str_to_terminal("\n");
		sl_put_colored_str_to_terminal("GAME OVER !", STR_RED);
		collected = env->tex.bomb.collected - 1;
		to_collect = env->tex.bomb.to_collect;
		sl_put_str_to_terminal("> Collected items:\t");
		sl_put_nbr_to_terminal(collected);
		sl_put_str_to_terminal("/");
		sl_put_nbr_to_terminal(to_collect);
		sl_put_str_to_terminal("\n");
		sl_put_steps_on_terminal(env);
		sl_exit_game(env);
	}
	++time;
}
