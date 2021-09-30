/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:01:27 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/05/24 02:54:14 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ppx_printf.h"

t_sharp	ft_print_o_shp(t_flags *arg, unsigned int o)
{
	int		len;
	t_sharp	shp;

	ft_bzero(&shp, sizeof(shp));
	ft_check_arg(arg, o);
	len = ft_baselen(o, 8);
	shp.len = len;
	shp.zero = ft_count_zero(arg, len);
	if (arg->sharp && !shp.zero)
		ft_putnchar(arg, '0', 1);
	return (shp);
}

void	ft_process_o(va_list ap, t_flags *arg)
{
	unsigned int	o;
	t_sharp			shp;

	o = va_arg(ap, unsigned int);
	shp = ft_print_o_shp(arg, o);
	if (arg->minus)
	{
		ft_print_zero(arg, shp.zero);
		if (!(arg->dot && arg->max == 0))
			ft_print_oct(arg, o);
		ft_print_space(arg, shp.zero + shp.len);
	}
	else
	{
		ft_print_space(arg, shp.zero + shp.len);
		ft_print_zero(arg, shp.zero);
		if (!(arg->dot && arg->max == 0))
			ft_print_oct(arg, o);
	}
}

void	ft_process_p(va_list ap, t_flags *arg)
{
	size_t	h;
	int		zero;
	int		len;

	h = va_arg(ap, size_t);
	ft_check_arg(arg, h);
	if (h)
		len = ft_baselen(h, 16) + 2;
	else
		len = 5;
	zero = ft_count_zero(arg, len);
	if (arg->minus)
	{
		ft_print_zero(arg, zero);
		if (!(arg->dot && arg->max == 0))
			ft_print_p(arg, h);
		ft_print_space(arg, zero + len);
	}
	else
	{
		ft_print_space(arg, zero + len);
		ft_print_zero(arg, zero);
		if (!(arg->dot && arg->max == 0))
			ft_print_p(arg, h);
	}
}
