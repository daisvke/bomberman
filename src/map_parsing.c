/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 03:44:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/29 14:14:58 by dtanigaw         ###   ########.fr       */
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
void	sl_populate_map_with_elem(t_data *data, char char_to_check, int x, int y)
{
	int	i;

	i = 0;
	while (MAP_ELEMS[i])
	{
		if (char_to_check == MAP_ELEMS[i])
		{
			data->map[y][x] = i + '0';
			return ;
		}
		++i;
	}
}

void	sl_parse_map(t_data *data, char *filename)
{
	char	*line;
	int		map_fd;
	int		i;
	int		j;

	map_fd = open(filename, O_RDONLY);
	i = 0;
	while (get_next_line(map_fd, &line))
	{
		j = 0;
		while (line[j])
		{
			sl_populate_map_with_elem(data, line[j], j, i);
			++j;
		}
		free(line);
		++i;
	}
	free(line);
	line = NULL;
} 
