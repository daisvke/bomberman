/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 03:44:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/06 20:58:19 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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

void	sl_check_errors_2(t_env *env, int res)
{
	if (res == ERROR)
		env->errors[18] = true;
	if (env->height < 2 || env->width < 2)
		env->errors[19] = true;
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
	env->height = i;
	close(map_fd);
	line = ft_free(line);
	sl_check_errors_2(env, res);
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

t_count	sl_init_counter(void)
{
	t_count	counter;

    counter.player = 0;
	counter.collectible = 0;
    counter.exit_pipe = 0;
	return (counter);
}

void	sl_parse_map_with_gnl(t_env *env, int map_fd, t_count *counter)
{
	char	*line;
	t_coord	pos;
	int		i;
	int		j;

	i = 0;
	while (get_next_line(map_fd, &line))
	{
		env->map[i] = malloc(sizeof(*env->map) * (ft_strlen(line) + 1));
		if (!env->map[i])
			env->errors[20] = true;
		j = 0;
		while (line[j])
		{
			pos = sl_assign_pos(j, i);
			sl_populate_map_with_textures(env, line[j], pos, counter);
			++j;
		}
		line[j] = '\0';
		free(line);
		++i;
	}
	env->map[i] = NULL;
	free(line);
	line = NULL;
}

void	sl_parse_map(t_env *env, char *filename)
{
	int		map_fd;
    t_count counter;

	sl_get_window_dimensions(env, filename);
	env->map = ft_malloc(env, env->height + 1, sizeof(*env->map));
	map_fd = open(filename, O_RDONLY);
	counter = sl_init_counter();
	sl_parse_map_with_gnl(env, map_fd, &counter);
	close(map_fd);
    sl_check_counter(env, counter);
} 
