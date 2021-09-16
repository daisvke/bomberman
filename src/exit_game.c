/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:51:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/16 03:52:05 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int    sl_exit_game(t_env *env)
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
		ft_free(env->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

void    sl_print_err_message(t_env *env, int err_code)
{
	char	*err_message;

	err_message = NULL;
	printf("\n");
	printf("Error code: %d", err_code);
	err_message = sl_get_err_message_from_err_code(err_code);
	printf("%s\t\t%s%s\n\n", STR_RED, err_message, STR_WHITE);
}

void    sl_put_err_code_and_exit_if_map_is_incomplete(t_env *env, \
	int err_code, int i)
{
	char	*err_message;

	sl_free_map_when_not_complete(env, env->map, i);
	err_message = NULL;
	printf("\n");
	printf("Error code: 20");
	err_message = sl_get_err_message_from_err_code(20);
	printf("%s\t\t%s%s\n\n", STR_RED, err_message, STR_WHITE);
	exit(EXIT_SUCCESS);
}

void    sl_put_err_code_and_exit_game(t_env *env, int err_code)
{
	char	*err_message;

	err_message = NULL;
	printf("\n");
	printf("Error code: %d", err_code);
	err_message = sl_get_err_message_from_err_code(err_code);
	printf("%s\t\t%s%s\n\n", STR_RED, err_message, STR_WHITE);
	sl_exit_game(env);
}

void	sl_exit_when_game_clear(t_env *env, char **map, int x, int y)
{
	static int	time;
	int			collected;
	int			to_collect;
	char		*count;

	if (time <= CENTER_MESS_TIME * 2)
		sl_put_centered_message_to_window(env, "GAME CLEAR !");
	else
	{
		printf("\n");
		printf("%s\t\tGAME CLEAR !%s\n\n", STR_CYAN, STR_WHITE);
		count = ft_itoa(env, env->p1.moves);
		printf("> Steps:\t\t%s\n", count);
		printf("\n");
		sl_exit_game(env);
	}
	++time;
}

void	sl_exit_when_game_over(t_env *env)
{
	static int	time;
	int			collected;
	int			to_collect;
	char		*count;

	if (time <= CENTER_MESS_TIME)
		sl_put_centered_message_to_window(env, "GAME OVER !");
	else
	{
		printf("\n");
		printf("%s\t\tGAME OVER !%s\n\n", STR_RED, STR_WHITE);
		collected = env->tex.bomb.collected - 1;
		to_collect = env->tex.bomb.to_collect;
		printf("> Collected items:\t%d/%d\n", collected, to_collect);
		count = ft_itoa(env, env->p1.moves);
		printf("> Steps:\t\t%s\n", count);
		printf("\n");
		sl_exit_game(env);
	}
	++time;
}
