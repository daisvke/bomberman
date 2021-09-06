/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 05:35:13 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/06 22:40:11 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_open(t_env *env, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
		sl_set_err_code_and_exit_game(env, 21);
	return (fd);
}

void	ft_close(t_env *env, int fd)
{
	if (close(fd) == ERROR)
		sl_set_err_code_and_exit_game(env, 22);
}

void	*ft_free(void *ptr)
{
    if (ptr)
        free(ptr);
	return (NULL);
}

void	*ft_malloc(t_env *env, size_t num, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(num * size);
	if (!ptr)
		sl_set_err_code_and_exit_game(env, 20);
	return (ptr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned)s1[i] - (unsigned)s2[i]);
}

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
