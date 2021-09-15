/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 03:44:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/15 13:16:16 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	sl_get_width(t_env *env, char *line)
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
	map_fd = ft_open(env, filename);
	if (map_fd == ERROR)
		env->errors[16] = true;
	i = 0;
	res = 1;
	while (res > 0)
	{
		res = get_next_line(map_fd, &line);
		if (res <= 0)
			break ;
		env->width = sl_get_width(env, line);
		ft_free(line);
		++i;
	}
	env->height = i;
	ft_close(env, map_fd);
	line = ft_free(line);
	sl_check_errors_2(env, res);
}

void	sl_read_line_and_populate_map(t_env *env, char *line, int i, t_count *c)
{
	int		j;
	t_coord	pos;

	j = 0;
	while (line[j])
	{
		pos = sl_assign_pos(j, i);
		sl_populate_map_with_textures(env, line[j], pos, c);
		++j;
	}
}

void	sl_parse_map_with_gnl(t_env *env, int map_fd, t_count *counter)
{
	char	*line;
	int		res;
	int		i;

	i = 0;
	res = 1;
	while (res > 0)
	{
		res = get_next_line(map_fd, &line);
		if (res <= 0)
			break ;
		env->map[i] = malloc(sizeof(*env->map) * (ft_strlen(line) + 1));
		if (!env->map[i])
			sl_put_err_code_and_exit_if_map_is_incomplete(env, 20, i);
		sl_read_line_and_populate_map(env, line, i, counter);
		free(line);
		++i;
	}
	env->map[i] = NULL;
	line = ft_free(line);
	sl_check_errors_2(env, res);
}

void	sl_parse_map(t_env *env, char *filename)
{
	int		map_fd;
    t_count counter;

	sl_get_window_dimensions(env, filename);
	env->map = ft_malloc(env, env->height + 1, sizeof(*env->map));
	map_fd = ft_open(env, filename);
	counter = sl_init_counter();
	sl_parse_map_with_gnl(env, map_fd, &counter);
	ft_close(env, map_fd);
    sl_check_counter(env, counter);
} 
