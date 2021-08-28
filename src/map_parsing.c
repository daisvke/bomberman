/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 03:44:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/28 04:51:17 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
char    *ft_strchr(const char *s, int c)
{
        while (*s)
        {
                if (*s == (char)c)
                        return ((char *)s);
                s++;
        }
        if (!(char)c)
                return ((char *)s);
        return (0);
}

void	sl_check_if_map_is_surrounded_by_walls(t_env *env, int x, int y, int texture)
{
	if (x == 0 || y == 0 || x == env->width || y == env->height)
	{
		if (texture != MAP_WALL - '0')
		{
			printf("no walls\n");
			exit(EXIT_FAILURE);
		}
	}
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
		sl_exit_game(env, "Error: too many ennemies on the map");
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
			sl_exit_game(env, "Error: too many bomb items on the map");
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
			sl_exit_game(env, "Error: too many fire items on the map");
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
			sl_exit_game(env, "Error: too many speed items on the map");
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
	exit(EXIT_FAILURE);//error message
		// exut but no mlx destroy
//		else
//			sl_exit_game(env, "Error: unknown element on the map file");
}

void	sl_get_window_dimensions(t_env *env, char *filename)
{
	char	*line;
	int		i;
	int		j;
	int		map_fd;

	map_fd = open(filename, O_RDONLY);
	if (map_fd == ERROR)
		exit(EXIT_FAILURE);
	i = 0;
	while (get_next_line(map_fd, &line) && ft_strlen(line) != 0)
	{
		j = 0;
		while (line[j])
			++j;
		if (j > 0)
			env->width = j;
		if (env->width && j != env->width)
			exit(EXIT_FAILURE);
		free(line);
		++i;
	}
	// if error
	free(line);
	line = NULL;
	env->height = i;
	close (map_fd);
	//this but without mlx destroy
//	if (env->height == env->width)
	//	sl_exit_game(env, "Error: the map is a square but has to be a rectangle");
}

void    sl_check_counter(t_env *env, t_count counter)
{
    if (!counter.collectible)
		sl_exit_game(env, "Error: the map has to contain at least one collectible");
    if (!counter.player || counter.player > 1)
		sl_exit_game(env, "Error: the map has to contain one player");
    if (!counter.exit_pipe)
		sl_exit_game(env, "Error: the map has to contain an exit");
}

void	sl_parse_map(t_env *env, char *filename)
{
	char	*line;
	int		map_fd;
	int		i;
	int		j;
    t_count counter;

	map_fd = open(filename, O_RDONLY);
	sl_get_window_dimensions(env, filename);
	env->map = malloc(env->height * sizeof(*env->map));
    counter.player = 0;
	counter.collectible = 0;
    counter.exit_pipe = 0;
	i = 0;
	while (get_next_line(map_fd, &line))
	{
		env->map[i] = malloc(ft_strlen(line) * sizeof(*env->map));
		//ft_malloc error + free
		j = 0;
		while (line[j])
		{
			sl_populate_map_with_textures(env, line[j], j, i, &counter);
			++j;
		}
		free(line);
		++i;
	}
	close (map_fd);
    sl_check_counter(env, counter);
	// if error
	free(line);
	line = NULL;
} 
