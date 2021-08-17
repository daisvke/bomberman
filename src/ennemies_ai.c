/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies_ai.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:23:20 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/17 22:37:15 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_assign_ennemy_curr_dir(t_sprite *sprite, int i)
{
	if (i == 0)
		sprite->curr_dir.up = true;
	if (i == 1)
		sprite->curr_dir.down = true;
	if (i == 2)
		sprite->curr_dir.left = true;
	if (i == 3)
		sprite->curr_dir.right = true;
}

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

int	sl_keep_direction_if_no_wall(char **map, t_dir curr_dir, int pos_x, int pos_y)
{
	if (curr_dir.up == true && map[pos_y - 1][pos_x] != MAP_WALL)
		return (KEEP);
	if (curr_dir.down == true && map[pos_y + 1][pos_x] != MAP_WALL)
		return (KEEP);
	if (curr_dir.left == true && map[pos_y][pos_x - 1] != MAP_WALL)
		return (KEEP);
	if (curr_dir.right == true && map[pos_y][pos_x + 1] != MAP_WALL)
		return (KEEP);
	return (0);
}

void	sl_determine_ennemy_direction(t_env *env, t_sprite *sprite)
{
	char	**map;
	int	pos_x;
	int	pos_y;
	int	len_array[4];
	int	keep;

	map = env->map;
	pos_x = sprite->pos.x;
	pos_y = sprite->pos.y;

	keep = sl_keep_direction_if_no_wall(map, sprite->curr_dir, pos_x, pos_y);
	if (keep == true)
		return ;
	sprite->curr_dir.up = false;
	sprite->curr_dir.down = false;
	sprite->curr_dir.left = false;
	sprite->curr_dir.right = false;
	 int i=0;
	while (i < 4)
	{
		len_array[i] = 0;
		++i;
	}
	while (pos_y >= 0 && map[pos_y][pos_x] != MAP_WALL)
	{
		if (map[pos_y][pos_x] == MAP_PLAYER)
		{
			sprite->curr_dir.up = true;
			return ;
		}
		++len_array[UP_LEN];
		--pos_y;
	}
	pos_x = sprite->pos.x;
	pos_y = sprite->pos.y;
	while (pos_y < env->height && map[pos_y][pos_x] != MAP_WALL)
	{
		if (map[pos_y][pos_x] == MAP_PLAYER)
		{
			sprite->curr_dir.down = true;
			return ;
		}
		++len_array[DOWN_LEN];
		++pos_y;
	}
	pos_x = sprite->pos.x;
	pos_y = sprite->pos.y;
	while (pos_x >= 0 && map[pos_y][pos_x] != MAP_WALL)
	{
		if (map[pos_y][pos_x] == MAP_PLAYER)
		{
			sprite->curr_dir.left = true;
			return ;
		}
		++len_array[LEFT_LEN];
		--pos_x;
	}
	pos_x = sprite->pos.x;
	pos_y = sprite->pos.y;
	while (pos_x < env->width && map[pos_y][pos_x] != MAP_WALL)
	{
		if (map[pos_y][pos_x] == MAP_PLAYER)
		{
			sprite->curr_dir.right = true;
			return ;
		}
		++len_array[RIGHT_LEN];
		++pos_x;
	}
	sl_get_max_len(sprite, len_array);
}

void	sl_read_and_animate_ennemies(t_env *env)
{
	bool	is_alive;
	int		ennemies_count;
	int		i;

	ennemies_count = env->tex.ennemies.count;
	i = 0;
	while (i < ennemies_count)
	{
		is_alive = env->tex.ennemies.sprites[i].alive;
		if (is_alive == true)
		{
			sl_determine_ennemy_direction(env, &env->tex.ennemies.sprites[i]);
		//	sl_read_direction_and_animate_sprite(env, &env->tex.ennemies.sprites[i].curr_dir, &env->tex.ennemies.sprites[i], ENNEMY, &env->p1.img);
			sl_read_direction_and_animate_sprite(env, &env->tex.ennemies.sprites[i].curr_dir, &env->tex.ennemies.sprites[i], ENNEMY, &env->tex.ennemies.img);
		}
		++i;
	}
}

