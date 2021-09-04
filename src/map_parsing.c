/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 03:44:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/05 00:30:12 by dtanigaw         ###   ########.fr       */
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
		if (texture != MAP_WALL - '0')
			env->error = true;
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
			sl_set_err_code_and_exit_game(env, 8);
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
			sl_set_err_code_and_exit_game(env, 9);
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
			sl_set_err_code_and_exit_game(env, 10);
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
	sl_set_err_code_and_exit_game(env, 12);
}

void	sl_exit_cleanly_when_gnl_fails(t_env *env, int err_code, char *line, int map_fd)
{
	close(map_fd);
	ft_free(line);
	line = NULL;
	sl_set_err_code_and_exit_game(env, err_code);
}

void	sl_get_window_dimensions(t_env *env, char *filename)
{
	char	*line;
	int		i;
	int		j;
	int		map_fd;
	int		res;

	line = NULL;
	map_fd = open(filename, O_RDONLY);
	if (map_fd == ERROR)
		sl_exit_cleanly_when_gnl_fails(env, 16, line, map_fd);
	i = 0;
	res = 1;
	while (res > 0)
	{
		res = get_next_line(map_fd, &line);
		if (res <= 0)
			break ;
		j = 0;
		while (line[j])
			++j;
		env->width = j;
		if (env->width && j != env->width)
			sl_exit_cleanly_when_gnl_fails(env, 17, line, map_fd);
		ft_free(line);
		++i;
	}
	close (map_fd);
	ft_free(line);
	line = NULL;
	if (res == ERROR)
		sl_set_err_code_and_exit_game(env, 18);
	env->height = i;
	if (env->height < 2 || env->width < 2)
		sl_set_err_code_and_exit_game(env, 19);
}

void    sl_check_counter(t_env *env, t_count counter)
{
    if (!counter.collectible)
		sl_set_err_code_and_exit_game(env, 13);
    if (!counter.player || counter.player > 1)
		sl_set_err_code_and_exit_game(env, 14);
    if (!counter.exit_pipe)
		sl_set_err_code_and_exit_game(env, 15);
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
	env->map = malloc(sizeof(*env->map) * (env->height + 1));
    counter.player = 0;
	counter.collectible = 0;
    counter.exit_pipe = 0;
	i = 0;
	while (get_next_line(map_fd, &line))
	{
		env->map[i] = malloc(sizeof(*env->map) * (ft_strlen(line) + 1));
		//ft_malloc error + free
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
	if (env->error == true)
		sl_set_err_code_and_exit_game(env, 11);
    sl_check_counter(env, counter);
	// if error
	free(line);
	line = NULL;
} 
