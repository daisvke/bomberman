/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:34:01 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/03 20:30:16 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_coord	sl_assign_pos(int x, int y)
{
	t_coord	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

int	sl_nbrlen(long long int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n = -n;
		len = sl_nbrlen(n) + 1;
	}
	else
	{
		while (n > 0)
		{
			len += 1;
			n = n / 10;
		}
	}
	return (len);
}

char	*sl_itoa(t_env *env, int n)
{
	char	*res;
	int		len;
	long	nb;

	nb = n;
	len = sl_nbrlen(nb);
	res = malloc(sizeof(*res) * (len + 1));
	if (!res)
		sl_put_err_code_and_exit_game(env, 20);
	res[len] = '\0';
	if (nb < 0)
		nb = -nb;
	while (len--)
	{
		res[len] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
