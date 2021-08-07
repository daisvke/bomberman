/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 03:44:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/07 11:29:36 by dtanigaw         ###   ########.fr       */
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
		if (texture != WALL - '0')
		{
			printf("no walls\n");
			exit(EXIT_FAILURE);
		}
	}
}

void	sl_populate_map_with_textures(t_env *env, char char_to_check, int x, int y,t_count *counter)
{
	int		i;
	t_exit	*game_exit;

	game_exit = &env->tex.exit;
	i = 0;
	while (MAP_ELEMS[i])
	{
		if (char_to_check == MAP_ELEMS[i])
		{
			sl_check_if_map_is_surrounded_by_walls(env, x, y, i);
			env->map[y][x] = i + '0';
			if (i == BOMB)
				++env->tex.bomb.to_collect;
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
                ++counter->exit;
				game_exit->pos.x = x;
				game_exit->pos.y = y;
			}	
			return ;
		}
		++i;
	}
	exit(EXIT_FAILURE);//error message
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
	if (env->height == env->width)
		exit(EXIT_FAILURE);
}

void    sl_check_counter(t_count counter, int bomb_count)
{
    if (!bomb_count)
        exit(EXIT_FAILURE);
    if (!counter.player || counter.player > 1)
        exit(EXIT_FAILURE);
    if (!counter.exit)
        exit(EXIT_FAILURE);;
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
    counter.exit = 0;
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
    sl_check_counter(counter, env->tex.bomb.to_collect);
	// if error
	free(line);
	line = NULL;
} 
