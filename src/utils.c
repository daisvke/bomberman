/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:34:01 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/06 19:34:30 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_coord	sl_assign_pos(int x, int y)
{
	t_coord	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}