/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 03:44:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/05 14:50:25 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_check_if_map_is_surrounded_by_walls(t_env *env, int x, int y, int texture)
{
	if (x == 0 || y == 0 || x == env->width || y == env->height)
		if (texture != MAP_WALL - '0')
			env->errors[11] = true;
}

void	sl_read_ennemies_from_map(t_env *env, int x, int y)
{
	t_sprite	*ennemies;
	int			*ennemies_count;
	static int	i;

	ennemies = env->tex.ennemies.sprites;
	ennemies_count = &env->tex.ennemies.count;
	*ennemies_count += 1;
	if (*ennemies_count >= ENNEMY_LIMIT)
		sl_set_err_code_and_exit_game(env, 7);
	sl_init_sprite(&ennemies[i], x, y, ENNEMY_SPEED);
	++i;
}

void	sl_assign_collectible_type_randomly(t_env *env, int x, int y)
{
	static int	j;
	static int	k;
	static int	l;
	char		**map;

	map = env->map;
	if (j == 0 || x % 2 == 0)
	{
		if (j >= ITEM_LIMIT)
			env->errors[8] = true;
		map[y][x] = 'B';
		env->tex.bomb.item_bombs[j].pos.x = x;
		env->tex.bomb.item_bombs[j].pos.y = y;
		env->tex.bomb.item_bombs[j].draw = true;
		++env->tex.bomb.to_collect;
		++j;
	}
	else if (x % 3 == 0)
	{
		if (k >= ITEM_LIMIT)
			env->errors[9] = true;
		map[y][x] = 'F';
		env->tex.fire.items[k].pos.x = x;
		env->tex.fire.items[k].pos.y = y;
		env->tex.fire.items[k].draw = true;
		++env->tex.fire.to_collect;
		++k;
	}
	else 
	{
		if (l >= ITEM_LIMIT)
			env->errors[10] = true;
		map[y][x] = 'S';
		env->tex.speed.items[l].pos.x = x;
		env->tex.speed.items[l].pos.y = y;
		env->tex.speed.items[l].draw = true;
		++env->tex.speed.to_collect;
		++l;
	}
}

void	sl_populate_map_with_textures(t_env *env, char char_to_check, int x, int y, t_count *counter)
{
	int		i;
	t_pipe	*game_exit;

	game_exit = &env->tex.exit_pipe;
	i = 0;
	while (MAP_ELEMS[i])
	{
		if (char_to_check == MAP_ELEMS[i])
		{
			sl_check_if_map_is_surrounded_by_walls(env, x, y, i);
			if (i != COLLECTIBLE)
				env->map[y][x] = i + '0';
			else
			{
				++counter->collectible;
				sl_assign_collectible_type_randomly(env, x, y);
			}
			if (i == PLAYER)
			{
                ++counter->player;
				env->p1.pos.x = x;
				env->p1.pos.y = y;
				env->p1.sub_pos.x = x * BLOC_LEN;
				env->p1.sub_pos.y = y * BLOC_LEN;
			}
			if (i == EXIT)
			{
                ++counter->exit_pipe;
				game_exit->pos.x = x;
				game_exit->pos.y = y;
			}
            if (i == ENNEMY)
				sl_read_ennemies_from_map(env, x, y);
			return ;
		}
		++i;
	}
	env->errors[12] = true;
}

int	sl_get_width(t_env *env, char *line, int map_fd, int height)
{
	int		j;

	j = 0;
	while (line[j])
		++j;
	if (env->width && j != env->width)
		env->errors[17] = true;
	return (j);
}

void	sl_get_window_dimensions(t_env *env, char *filename)
{
	char	*line;
	int		i;
	int		map_fd;
	int		res;

	line = NULL;
	map_fd = open(filename, O_RDONLY);
	if (map_fd == ERROR)
		env->errors[16] = true;
	i = 0;
	res = 1;
	while (res > 0)
	{
		res = get_next_line(map_fd, &line);
		if (res <= 0)
			break ;
		env->width = sl_get_width(env, line, map_fd, i);
		ft_free(line);
		++i;
	}
	close(map_fd);
	line = ft_free(line);
	if (res == ERROR)
		env->errors[18] = true;
	env->height = i;
	if (env->height < 2 || env->width < 2)
		env->errors[19] = true;
}

void    sl_check_counter(t_env *env, t_count counter)
{
    if (!counter.collectible)
		env->errors[13] = true;
    if (!counter.player || counter.player > 1)
		env->errors[14] = true;
    if (!counter.exit_pipe)
		env->errors[15] = true;
}

void	sl_parse_map(t_env *env, char *filename)
{
	char	*line;
	int		map_fd;
	int		i;
	int		j;
    t_count counter;

	sl_get_window_dimensions(env, filename);
	env->map = ft_malloc(env, env->height + 1, sizeof(*env->map));
    counter.player = 0;
	counter.collectible = 0;
    counter.exit_pipe = 0;
	map_fd = open(filename, O_RDONLY);
	i = 0;
	while (get_next_line(map_fd, &line))
	{
		env->map[i] = malloc(sizeof(*env->map) * (ft_strlen(line) + 1));
		if (!env->map[i])
			env->errors[20] = true;
		j = 0;
		while (line[j])
		{
			sl_populate_map_with_textures(env, line[j], j, i, &counter);
			++j;
		}
		line[j] = '\0';
		free(line);
		++i;
	}
	env->map[i] = NULL;
	close(map_fd);
    sl_check_counter(env, counter);
	free(line);
	line = NULL;
} 
