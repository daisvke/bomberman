/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_items.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:39:22 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/03 21:31:42 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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

void	sl_assign_values_by_collectible_type(t_env *env, t_coord pos, \
	char code, int i, int err)
{
	t_items	*item;
	char	**map;
	int		*collected;

	map = env->map;
	collected = NULL;
	item = sl_get_item_by_its_code(env, code, &collected, i);
	if (i >= ITEM_LIMIT)
		env->errors[err] = true;
	map[pos.y][pos.x] = code;
	item->pos.x = pos.x;
	item->pos.y = pos.y;
	item->draw = true;
	*collected += 1;
}

void	sl_assign_collectible_type_randomly(t_env *env, t_coord pos, int *count)
{
	static int	i;
	static int	j;
	static int	k;
	char		**map;

	map = env->map;
	if (i == 0 || pos.x % 2 == 0)
	{
		sl_assign_values_by_collectible_type(env, pos, 'B', i, 8);
		++i;
	}
	else if (pos.x % 3 == 0)
	{
		sl_assign_values_by_collectible_type(env, pos, 'F', j, 9);
		++j;
	}
	else
	{
		sl_assign_values_by_collectible_type(env, pos, 'S', k, 10);
		++k;
	}
	*count += 1;
}
