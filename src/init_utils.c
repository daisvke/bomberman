/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:41:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/03 20:51:40 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	sl_init_array(int *array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		array[i] = 0;
		++i;
	}
}

void	sl_init_errors(t_env *env)
{
	int	i;

	i = 0;
	while (i <= ERR_MAX)
	{
		env->errors[i] = false;
		++i;
	}
}

void	sl_check_errors_1(t_env *env)
{
	int		i;
	bool	quit;

	quit = false;
	i = 0;
	while (i <= ERR_MAX)
	{
		if (env->errors[i] == true)
		{
			sl_print_err_message(i);
			quit = true;
		}
		++i;
	}
	if (quit == true)
		sl_exit_game(env);
}

t_count	sl_init_counter(void)
{
	t_count	counter;

	counter.player = 0;
	counter.collectible = 0;
	counter.exit_pipe = 0;
	return (counter);
}

void	sl_init_mlx(t_env *env, int width, int height)
{
	char	*title;

	env->mlx_ptr = mlx_init();
	if (!env->mlx_ptr)
		sl_put_err_code_and_exit_game(env, 1);
	title = "minibomberman";
	env->win_ptr = mlx_new_window(env->mlx_ptr, width, height, title);
	if (!env->win_ptr)
		sl_put_err_code_and_exit_game(env, 2);
}
