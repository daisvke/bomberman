/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:43 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/16 04:52:19 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	sl_free_buffer(int *buffer[], int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		sl_free(buffer[i]);
		++i;
	}
	buffer = sl_free(buffer);
}

void	sl_free_map(t_env *env, char *map[])
{
	int	i;

	i = 0;
	while (i < env->height)
	{
		sl_free(map[i]);
		++i;
	}
	map = sl_free(map);
}

void	sl_free_map_when_not_complete(char *map[], int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		sl_free(map[i]);
		++i;
	}
	map = sl_free(map);
}
