/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:46:43 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/15 16:48:20 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_free_buffer(int *buffer[], int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		ft_free(buffer[i]);
		++i;
	}
	buffer = ft_free(buffer);
}

void	sl_free_map(t_env *env, char *map[])
{
	int	i;

	i = 0;
	while (i < env->height)
	{
		ft_free(map[i]);
		++i;
	}
	map = ft_free(map);
}

void	sl_free_map_when_not_complete(t_env *env, char *map[], int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		ft_free(map[i]);
		++i;
	}
	map = ft_free(map);
}
