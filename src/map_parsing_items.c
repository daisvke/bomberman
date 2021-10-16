/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_items.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:39:22 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/15 19:08:44 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_items	*sl_get_item_by_its_code(t_env *env, int code, int **collected, int i)
{
	t_items	*item;

	if (code == 'B')
	{
		item = &env->tex.bomb.item_bombs[i];
		*collected = &env->tex.bomb.to_collect;
	}
	if (code == 'F')
	{
		item = &env->tex.fire.items[i];
		*collected = &env->tex.fire.to_collect;
	}
	if (code == 'S')
	{
		item = &env->tex.speed.items[i];
		*collected = &env->tex.speed.to_collect;
	}
	return (item);
}

void	sl_assign_values_by_collectible_type(\
	t_env *env, t_coord pos, t_info info)
{
	t_items	*item;
	char	**map;
	int		*collected;

	map = env->map;
	collected = NULL;
	item = sl_get_item_by_its_code(env, info.code, &collected, info.i);
	if (info.i >= ITEM_LIMIT)
		env->errors[info.err] = true;
	map[pos.y][pos.x] = info.code;
	item->pos.x = pos.x;
	item->pos.y = pos.y;
	item->draw = true;
	*collected += 1;
}

t_info	sl_assign_info(char code, int i, int err)
{
	t_info	info;

	info.code = code;
	info.i = i;
	info.err = err;
	return (info);
}

void	sl_assign_collectible_type_randomly(t_env *env, t_coord pos, int *count)
{
	static int	i;
	static int	j;
	static int	k;
	t_info		info;

	if (i == 0 || pos.x % 2 == 0)
	{
		info = sl_assign_info('B', i, 8);
		sl_assign_values_by_collectible_type(env, pos, info);
		++i;
	}
	else if (pos.x % 3 == 0)
	{
		info = sl_assign_info('F', j, 9);
		sl_assign_values_by_collectible_type(env, pos, info);
		++j;
	}
	else
	{
		info = sl_assign_info('S', k, 10);
		sl_assign_values_by_collectible_type(env, pos, info);
		++k;
	}
	*count += 1;
}
