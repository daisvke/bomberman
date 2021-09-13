/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 05:35:13 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/09 18:47:33 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_open(t_env *env, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == ERROR)
		sl_put_err_code_and_exit_game(env, 21);
	return (fd);
}

void	ft_close(t_env *env, int fd)
{
	if (close(fd) == ERROR)
		sl_put_err_code_and_exit_game(env, 22);
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
		sl_put_err_code_and_exit_game(env, 20);
	return (ptr);
}
