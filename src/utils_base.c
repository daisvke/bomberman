/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 04:46:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/05/04 04:50:39 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ppx_printf.h"

void	ft_print_hex(t_flags *arg, size_t nb, char *base)
{
	if (nb >= 16)
		ft_print_hex(arg, nb / 16, base);
	ft_putnchar(arg, base[nb % 16], 1);
}

void	ft_print_oct(t_flags *arg, unsigned int nb)
{
	if (nb >= 8)
		ft_print_oct(arg, nb / 8);
	ft_putnchar(arg, "012345678"[nb % 8], 1);
}

void	ft_print_p(t_flags *arg, size_t nb)
{
	if (!nb)
		ft_putstr_res(arg, "(nil)");
	else
	{
		ft_putstr_res(arg, "0x");
		ft_print_hex(arg, nb, HEX_LOWER);
	}
}

int	ft_baselen(size_t l, size_t base)
{
	int	len;

	len = 0;
	while (l >= base)
	{
		l /= base;
		++len;
	}
	++len;
	return (len);
}
