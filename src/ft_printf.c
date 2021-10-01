/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 00:00:40 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/30 18:23:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_init_arg(t_flags *arg)
{
	arg->zero = 0;
	arg->dot = 0;
	arg->min = 0;
	arg->max = 0;
	arg->sp = 0;
	arg->len = 0;
	arg->s = 0;
}

int	ppx_printf(const char *fmt, ...)
{
	va_list	ap;
	t_flags	arg;
	char	*s;

	if (!fmt)
		return (ERROR);
	s = ft_strdup(fmt);
	if (!s)
		return (ERROR);
	va_start(ap, fmt);
	ft_bzero(&arg, sizeof(arg));
	ft_read_fmt(&arg, ap, s);
	va_end(ap);
	free(s);
	s = NULL;
	return (arg.res);
}
