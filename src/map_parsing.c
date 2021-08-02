/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 03:44:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/02 14:12:15 by dtanigaw         ###   ########.fr       */
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
			if (i == BOMB)
				++data->bombs_to_collect;
			if (i == PLAYER)
			{
				data->player.x = x;
				data->player.y = y;
			}
			return ;
		}
		++i;
	}
	exit(EXIT_FAILURE);//error message
}

void	sl_get_window_dimensions(t_data *data, char *filename)
{
	char	*line;
	int		i;
	int		j;
	int		map_fd;

	map_fd = open(filename, O_RDONLY);
	i = 0;
	while (get_next_line(map_fd, &line) && ft_strlen(line) != 0)
	{
		j = 0;
		while (line[j])
			++j;
		if (j > 0)
			data->width = j * BLOC_PXL_LEN;
		free(line);
		++i;
	}
//	printf("width: %d", data->width);
	// if error
	free(line);
	line = NULL;
	data->height = i * BLOC_PXL_LEN;	
}

void	sl_parse_map(t_data *data, char *filename)
{
	char	*line;
	int		map_fd;
	int		i;
	int		j;

	map_fd = open(filename, O_RDONLY);
	sl_get_window_dimensions(data, filename);
//	printf("height: %d", data->height);
	data->map = malloc(data->height * sizeof(*data->map));
	i = 0;
	while (get_next_line(map_fd, &line))
	{
//		printf("strlen: %d\n", ft_strlen(line));
		data->map[i] = malloc(ft_strlen(line) * sizeof(*data->map));
		//ft_malloc
		j = 0;
		while (line[j])
		{
			sl_populate_map_with_elem(data, line[j], j, i);
			++j;
		}
		free(line);
		++i;
	}
	// if error
	free(line);
	line = NULL;
} 
