/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 04:01:42 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/13 04:02:48 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_get_max_len(t_sprite *sprite, int len_array[])
{
	int	max_len;
	int	i;

	i = 0;
	max_len = len_array[UP_LEN];
	while (i < 4)
	{
		if (len_array[i] > max_len)
			max_len = len_array[i];
		++i;
	}
	i = 0;
	while (i < 4)
	{
		if (len_array[i] == max_len)
			sl_assign_ennemy_curr_dir(sprite, i);
		++i;
	}
}
