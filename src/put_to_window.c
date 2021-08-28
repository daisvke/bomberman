/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:19:22 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/26 03:38:23 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_put_counts_to_window(t_env *env)
{
	char	*count;
	char	*collected;
	char	*to_collect;
//if error
	sl_render_bloc_with_xpm(&env->canvas, &env->p1.icon, 15, 0, true);
	count = ft_itoa(env->p1.moves);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 45, 17, 0xFFFFFF, count);
	free(count);
	sl_render_bloc_with_xpm(&env->canvas, &env->icon_bomb, 60, 0, true);
	collected = ft_itoa(env->tex.bomb.collected - 1);
	to_collect = ft_itoa(env->tex.bomb.to_collect);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 90, 17, 0xFFFFFF, collected);
	free(collected);
	mlx_string_put(env->mlx_ptr, env->win_ptr, 100, 17, 0xFFFFFF, "/");
	mlx_string_put(env->mlx_ptr, env->win_ptr, 110, 17, 0xFFFFFF, to_collect);
	free(to_collect);
}

void	sl_put_centered_message_to_window(t_env *env, char *message)
{
	static int	i;
	int			width;
	int			height;

	width = env->width * BLOC_LEN;
	height = env->height * BLOC_LEN;
	mlx_set_font(env->mlx_ptr, env->win_ptr, "7x14");
	if (i <= 3200)
		mlx_string_put(env->mlx_ptr, env->win_ptr, width / 2, height / 2, 0xFFFFFF, message);
	++i;
}
