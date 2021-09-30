/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:20:33 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/06/29 18:18:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ppx_printf.h"

void	ft_read_sp(t_flags *arg)
{
	if (ft_strchr(SP_LIST, *(arg->s)))
	{
		arg->sp = *(arg->s);
		arg->len++;
		arg->s++;
	}
}

void	ft_redirect_sp(va_list ap, t_flags *arg)	
{
	if (arg->sp == 'c')
		ft_process_c(ap, arg);
	else if (arg->sp == 's')
		ft_process_s(ap, arg);
	else if (arg->sp == 'p')
		ft_process_p(ap, arg);
	else if (arg->sp == 'd' || arg->sp == 'i')
		ft_process_di(ap, arg);
	else if (arg->sp == 'o')
		ft_process_o(ap, arg);
	else if (arg->sp == 'u')
		ft_process_u(ap, arg);
	else if (arg->sp == 'x')
		ft_process_x(ap, arg);
	else if (arg->sp == 'X')
		ft_process_x2(ap, arg);
	else if (arg->sp == 'n')
		ft_process_n(ap, arg);
	else if (arg->sp == '%')
		ft_process_per(arg);
}

bool	ft_redirect_fg(va_list ap, t_flags *arg)
{
	bool	err;

	err = 1;
	if (*(arg->s) == '#')
		ft_read_shp(arg);
	else if (*(arg->s) == 'h')
		ft_read_lm(arg);
	else if ((*(arg->s) == '0') || (*(arg->s) == '-'))
		ft_read_zero_minus(arg);
	else if (*(arg->s) == '+')
		ft_read_plus(arg);
	else if (*(arg->s) == ' ')
		ft_read_space(arg);
	else if (*(arg->s) == '*')
		err = ft_read_wc(arg, ap);
	else if (ft_isdigit(*(arg->s)))
		ft_read_nbr(arg);
	else if (*(arg->s) == '.')
		err = ft_read_dot(arg);
	return (err);
}

int	ft_set_flags(t_flags *arg, char *s, va_list ap)
{
	arg->len = 1;
	s++;
	arg->s = s;
	while (!ft_strchr(SP_LIST, *(arg->s)))
	{
		if (ft_strchr(FG_LIST, *(arg->s)))
		{
			if (!ft_redirect_fg(ap, arg))
				ft_init_arg(arg);
		}
		else
			break ;
	}
	ft_read_sp(arg);
	if (arg->minus && arg->zero)
		arg->zero = false;
	return (arg->res);
}

void	ft_read_fmt(t_flags *arg, va_list ap, char *s)
{
	arg->res = 0;
	while (*s)
	{
		ft_init_arg(arg);
		if (*s == '%')
		{
			ft_set_flags(arg, s, ap);
			if (arg->sp)
			{
				ft_redirect_sp(ap, arg);
				s += arg->len;
			}
			else
				ft_putchar_res(arg, *s++);
		}
		else
			ft_putchar_res(arg, *s++);
	}
}
