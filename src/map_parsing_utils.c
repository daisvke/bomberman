/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 22:38:44 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/06 23:21:23 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_check_errors_2(t_env *env, int res)
{
	if (res == ERROR)
		sl_put_err_code_and_exit_game(env, 16);
}

void	sl_check_counter(t_env *env, t_count counter)
{
	if (!counter.collectible)
		env->errors[13] = true;
	if (!counter.player || counter.player > 1)
		env->errors[14] = true;
	if (!counter.exit_pipe)
		env->errors[15] = true;
}
