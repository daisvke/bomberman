/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:41:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/05 14:41:57 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_init_errors(t_env *env)
{
	int	i;

	i = 0;
	while (i < ERR_MAX)
	{
		env->errors[i] = false;
		++i;
	}
}

void	sl_check_errors(t_env *env)
{
	int		i;
	bool	quit;

	quit = false;
	i = 0;
	while (i < ERR_MAX)
	{
		if (env->errors[i] == true)
		{
			sl_print_err_message(env, i);
			quit = true;
		}
		++i;
	}
	if (quit == true)
		sl_exit_game(env);
}
