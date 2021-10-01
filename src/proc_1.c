/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:01:07 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/05/04 05:01:05 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_process_s(va_list ap, t_flags *arg)
{
	char	*s;

	s = va_arg(ap, char *);
	if (!s)
	{
		if ((arg->dot && arg->max >= 6) || (!arg->dot && !arg->max) || \
			arg->max < 0)
			s = NULL_S;
		else if (arg->max < 6)
			s = "";
	}
	if (arg->max < 0)
		arg->max = ft_strlen(s);
	if ((arg->minus && arg->min) || (!arg->min && arg->dot && arg->max))
		ft_putnstr(arg, s, arg->max);
	if (arg->minus && !arg->dot && !arg->max)
		ft_putstr_res(arg, s);
	if (arg->min)
		ft_print_space(arg, ft_strlen(s));
	if (!arg->minus && arg->dot && arg->min)
		ft_putnstr(arg, s, arg->max);
	if (!arg->minus && !arg->dot && !arg->max)
		ft_putstr_res(arg, s);
}

void	ft_process_d(va_list ap, t_flags *arg)
{
	int		n;
	long	l;

	l = 0;
	n = va_arg(ap, int);
	if (n < 0)
		l = -n;
	if (l)
		ft_process_neg_nbr(arg, n, l);
	else
		ft_process_pos_nbr(arg, n);
}
