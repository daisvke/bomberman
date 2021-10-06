/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:07:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/06 22:54:43 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_get_char_index(char *str, char c, bool increment)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	if (increment)
		return (i);
	else
		return (NOT_FOUND);
}

char	*gnl_concatenate(char *s1, char *s2, int len, bool is_empty)
{
	char	*str;
	size_t	i;
	size_t	size;

	size = 0;
	if (s1 && is_empty == false)
		size += gnl_get_char_index(s1, '\0', true);
	if (s2)
		size += gnl_get_char_index(s2, '\0', true);
	if (len >= 0 && (int)size > len)
		size = len;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (is_empty == false && s1 && *s1 && i < size)
		str[i++] = *s1++;
	while (s2 && *s2 && i < size)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

int	gnl_get_line(char **data, int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			res;
	char		*tmp;

	res = 0;
	while (gnl_get_char_index(*data, '\n', false) == NOT_FOUND)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res < 0)
			return (ERROR);
		if (res == 0)
			break ;
		buffer[res] = '\0';
		tmp = gnl_concatenate(*data, buffer, OFF, false);
		if (!tmp)
			return (ERROR);
		free(*data);
		*data = tmp;
	}
	return (res);
}

int	gnl_run_and_return(char **data, char **line, int fd)
{
	int			res;
	size_t		index;
	char		*tmp;
	bool		is_empty;

	res = gnl_get_line(data, fd);
	if (res == ERROR)
		return (ERROR);
	index = 0;
	if (*data)
		index = gnl_get_char_index(*data, '\n', true);
	is_empty = index + 1 > gnl_get_char_index(*data, '\0', true);
	*line = gnl_concatenate(*data, NULL, index, false);
	if (!line)
		return (ERROR);
	tmp = gnl_concatenate(*data + index + 1, NULL, \
		gnl_get_char_index(*data, '\0', true) - index - 1, is_empty);
	if (!tmp)
		return (ERROR);
	free(*data);
	*data = tmp;
	if (res == REACHED_EOF && is_empty)
		return (REACHED_EOF);
	else
		return (LINE_READ);
}

int	get_next_line(int fd, char **line)
{
	static char	*data;
	char		*data_cpy;
	int			res;

	if (BUFFER_SIZE <= 0 || !line)
		return (ERROR);
	data_cpy = data;
	res = gnl_run_and_return(&data_cpy, line, fd);
	if (res == REACHED_EOF || res == ERROR)
	{
		free(data_cpy);
		data_cpy = NULL;
	}
	data = data_cpy;
	return (res);
}
