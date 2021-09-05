/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 05:35:13 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/05 00:42:15 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// include in libft
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
