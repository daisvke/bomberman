/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:30:09 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/09 19:15:29 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_alloc(char **line)
{
	char	*s;
	char	*p;

	s = (char *)malloc(sizeof(*s));
	if (!s)
		return (ERROR);
	p = s;
	*p = '\0';
	*line = s;
	return (0);
}

void	ft_join(char **line, char **s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*tmp_s1;
	char	*tmp_s2;
	char	*str;

	tmp_s1 = *s1;
	tmp_s2 = s2;
	str = (char *)malloc(sizeof(*str) * (ft_gnl_strlen(*s1) \
		+ ft_gnl_strlen(s2) + 1));
	if (!str)
		*line = NULL;
	i = 0;
	j = 0;
	while (tmp_s1[i])
		str[j++] = tmp_s1[i++];
	i = 0;
	while (tmp_s2[i])
		str[j++] = tmp_s2[i++];
	str[j] = '\0';
	*line = str;
	free(tmp_s1);
}

int	ft_get_prev(char **prev, int *pos, char **line)
{
	char	*tmp;

	*pos = ft_gnl_strchr(*prev, '\n');
	if (*pos >= 0)
	{
		free(*line);
		*line = ft_strsdup(*prev, *pos);
		tmp = ft_strsdup(*prev, ft_gnl_strlen(*prev));
		if (!*line || !tmp)
			*pos = ERROR2;
		free(*prev);
		*prev = ft_gnl_substr(tmp, *pos + 1, ft_gnl_strlen(tmp) - *pos);
		free(tmp);
		if (!prev)
			*pos = ERROR2;
		return (1);
	}
	free(*line);
	*line = ft_strsdup(*prev, ft_gnl_strlen(*prev));
	if (!*line)
		return (ERROR2);
	free(*prev);
	*prev = NULL;
	return (0);
}

int	ft_set_line(char **line, char **prev, char *buf, int r)
{
	char	*tmp;
	int		pos;

	pos = ft_gnl_strchr(buf, '\n');
	if (pos >= 0)
	{
		tmp = ft_strsdup(buf, pos);
		ft_join(line, line, tmp);
		if (!tmp || !*line)
			*line = NULL;
		free(tmp);
		if (*line && pos < r - 1)
		{
			*prev = ft_strsdup(&buf[pos + 1], r - pos - 1);
			if (!*prev)
				*line = NULL;
		}
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE + 1];
	static char	*prev;
	int			pos;

	if (read(fd, buf, 0) < 0 || !line || BUFFER_SIZE <= 0 || ft_alloc(line) < 0)
		return (ERROR);
	pos = 1;
	if (prev && ft_get_prev(&prev, &pos, line) && pos >= -1)
		return (LINE_READ);
	if (pos == ERROR2)
		return (ERROR);
	while (ft_gnl_bzero(buf, BUFFER_SIZE) && read(fd, buf, BUFFER_SIZE) != 0)
	{
		if (!*line || read(fd, buf, 0) < 0)
			return (ERROR);
		buf[ft_gnl_strlen(buf)] = '\0';
		if (ft_set_line(line, &prev, buf, ft_gnl_strlen(buf)) && *line)
			return (LINE_READ);
		if (!*line)
			return (ERROR);
		ft_join(line, line, buf);
		ft_gnl_bzero(buf, BUFFER_SIZE);
	}
	return (REACHED_EOF);
}
