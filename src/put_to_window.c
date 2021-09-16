/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:19:22 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/16 03:44:38 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_string_put(t_env *env, int x, int y, char *str)
{
	mlx_string_put(env->mlx_ptr, env->win_ptr, x, y, WHITE, str);
}

void	sl_put_message_at_start(t_env *env)
{
	static int	time;
	
	if (time <= CENTER_MESS_TIME)
	{
		sl_put_centered_message_to_window(env, "START !");
		++time;
	}
}

void	sl_put_stage_name(t_env *env)
{
	char	*str;
	int		width;
	int		height;

	width = env->width * BLOC_LEN;
	height = env->height * BLOC_LEN;
	mlx_set_font(env->mlx_ptr, env->win_ptr, "7x14");
	str = env->stage_name;
	sl_string_put(env, 10, height - 10, str);
}

void	sl_put_collectible_count_to_window(t_env *env)
{
	char	*count;
	char	*collected;
	char	*to_collect;
	t_coord	pos;

	pos = sl_assign_pos(15, 0);
	sl_render_bloc_with_xpm(&env->canvas, &env->p1.icon, pos, true);
	count = ft_itoa(env, env->p1.moves);
	sl_string_put(env, 45, 17, count);
	free(count);
	pos = sl_assign_pos(60, 0);
	sl_render_bloc_with_xpm(&env->canvas, &env->icon_bomb, pos, true);
	collected = ft_itoa(env, env->tex.bomb.collected - 1);
	to_collect = ft_itoa(env, env->tex.bomb.to_collect);
	sl_string_put(env, 90, 17, collected);
	free(collected);
	sl_string_put(env, 100, 17, "/");
	sl_string_put(env, 110, 17, to_collect);
	free(to_collect);
}

void	sl_put_centered_message_to_window(t_env *env, char *str)
{
	static int	time;
	int			str_len;
	int			width;
	int			height;

	str_len = ft_strlen(str) / 4;
	width = (env->width - str_len) * BLOC_LEN / 2;
	height = env->height * BLOC_LEN / 2;
	mlx_set_font(env->mlx_ptr, env->win_ptr, "7x14");
	if (time <= 3200)
		mlx_string_put(env->mlx_ptr, env->win_ptr, width, height, WHITE, str);
	++time;
}
