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

#include "../inc/so_long.h"

t_coord	sl_assign_pos(int x, int y)
{
	t_coord	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		++i;
	return ((unsigned)s1[i] - (unsigned)s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if (!(char)c)
		return ((char *)s);
	return (0);
}

int	ft_nbrlen(long long int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n = -n;
		len = ft_nbrlen(n) + 1;
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

char	*ft_itoa(t_env *env, int n)
{
	char	*res;
	int		len;
	long	nb;

	nb = n;
	len = ft_nbrlen(nb);
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
