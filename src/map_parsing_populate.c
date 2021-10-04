/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_populate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:32:25 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/04 04:53:28 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	sl_check_if_map_is_surrounded_by_walls(\
	t_env *env, t_coord pos, int texture)
{
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	if (x == 0 || y == 0 || x == env->width || y == env->height)
		if (texture != MAP_WALL - '0')
			env->errors[11] = true;
}

void	sl_read_ennemies_from_map(t_env *env, t_coord pos)
{
	t_sprite	*ennemies;
	int			*ennemies_count;
	static int	i;

	ennemies = env->tex.ennemies.sprites;
	ennemies_count = &env->tex.ennemies.count;
	*ennemies_count += 1;
	if (*ennemies_count >= ENNEMY_LIMIT)
		sl_put_err_code_and_exit_game(env, 7);
	sl_init_sprite(&ennemies[i], pos.x, pos.y, ENNEMY_SPEED);
	++i;
}

void	sl_assign_sprites_position(t_env *env, int i, t_coord pos, int *count)
{
	t_coord	*sprite_pos;
	t_coord	*sprite_sub_pos;

	sprite_sub_pos = NULL;
	if (i == PLAYER)
	{
		sprite_pos = &env->p1.pos;
		sprite_sub_pos = &env->p1.sub_pos;
	}
	if (i == EXIT)
		sprite_pos = &env->tex.exit_pipe.pos;
	*sprite_pos = sl_assign_pos(pos.x, pos.y);
	if (sprite_sub_pos)
		*sprite_sub_pos = sl_assign_pos(pos.x * BLOC_LEN, pos.y * BLOC_LEN);
	*count += 1;
}

void	sl_populate_map_with_textures(\
	t_env *env, char char_to_check, t_coord pos, t_count *counter)
{
	int		i;

	i = 0;
	while (MAP_ELEMS[i])
	{
		if (char_to_check == MAP_ELEMS[i])
		{
			sl_check_if_map_is_surrounded_by_walls(env, pos, i);
			if (i != COLLECTIBLE)
				env->map[pos.y][pos.x] = i + '0';
			else
				sl_assign_collectible_type_randomly(\
					env, pos, &counter->collectible);
			if (i == PLAYER)
				sl_assign_sprites_position(env, i, pos, &counter->player);
			if (i == EXIT)
				sl_assign_sprites_position(env, i, pos, &counter->exit_pipe);
			if (i == ENNEMY)
				sl_read_ennemies_from_map(env, pos);
			return ;
		}
		++i;
	}
	env->errors[12] = true;
}
