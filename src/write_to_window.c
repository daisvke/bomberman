/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:19:22 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/11 04:40:43 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_put_move_count_to_window(t_env *env)
{
	char	*count;
//if error
	count = ft_itoa(env->p1.moves);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 15, 15, 0xFFFFFF, count);
	free(count);
}

void	sl_put_centered_message_to_window(t_env *env, char *message)
{
	static int	i;
	int			width;
	int			height;

	width = env->width * BLOC_LEN;
	height = env->height * BLOC_LEN;
	mlx_set_font(env->mlx_ptr, env->win_ptr, "7x14");
//	if (i <= 3200)
		mlx_string_put(env->mlx_ptr, env->win_ptr, width / 2, height / 2, 0xFFFFFF, message);
	++i;
}
