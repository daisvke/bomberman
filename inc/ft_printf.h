/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ppx_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:25:30 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/06/29 18:25:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>
# include "../libft/libft.h"

# define SP_LIST "cspdiouxXn%"
# define FG_LIST "123456789."
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"
# define ERROR -1
# define EMPTY_FMT 0
# define NULL_S "(null)"

typedef struct s_flags
{
	bool	dot;
	int		min;	
	int		max;
	char	sp;
	int		len;
	char	*s;
	int		res;
}				t_flags;

int		ft_baselen(size_t l, size_t base);
void	ft_check_arg(t_flags *arg, long nb);
int		ft_count_zero(t_flags *arg, int len);
void	ft_init_arg(t_flags *arg);
int		ft_pos_nbr_count_space(t_flags *arg, int len, int zero);
int		ft_pos_nbr_count_zero(t_flags *arg, int len);
void	ft_print_di_l(t_flags *arg, int n, long l);
void	ft_print_hex(t_flags *arg, size_t nb, char *base);
void	ft_print_oct(t_flags *arg, unsigned int nb);
void	ft_print_p(t_flags *arg, size_t nb);
void	ft_print_space(t_flags *arg, int len);
void	ft_print_u(t_flags *arg, unsigned int nb);
void	ft_print_zero(t_flags *arg, int len);
int		ft_ppx_printf(const char *fmt, ...)
		__attribute__((format (ppx_printf, 1, 2)));
void	ft_process_c(va_list ap, t_flags *arg);
void	ft_process_s(va_list ap, t_flags *arg);
void	ft_process_di(va_list ap, t_flags *arg);
void	ft_process_n(va_list ap, t_flags *arg);
void	ft_process_neg_nbr(t_flags *arg, int n, long l);
void	ft_process_o(va_list ap, t_flags *arg);
void	ft_process_p(va_list ap, t_flags *arg);
void	ft_process_per(t_flags *arg);
void	ft_process_pos_nbr(t_flags *arg, long n);
void	ft_process_pos_nbr_u(t_flags *arg, long n);
void	ft_process_pos_nbr_umax(t_flags *arg);
void	ft_process_u(va_list ap, t_flags *arg);
void	ft_process_x(va_list ap, t_flags *arg);
void	ft_process_x2(va_list ap, t_flags *arg);
void	ft_putchar_res(t_flags *arg, char c);
void	ft_putnbr_res(t_flags *arg, long long int nb);
void	ft_putnchar(t_flags *arg, int c, size_t n);
void	ft_putnstr(t_flags *arg, char *s, int n);
void	ft_putstr_res(t_flags *arg, char *str);
bool	ft_read_dot(t_flags *arg);
void	ft_read_fmt(t_flags *arg, va_list ap, char *s);
void	ft_read_lm(t_flags *arg);
void	ft_read_nbr(t_flags *arg);
void	ft_read_space(t_flags *arg);
void	ft_read_plus(t_flags *arg);
void	ft_read_sp(t_flags *arg);
void	ft_read_shp(t_flags *arg);
bool	ft_read_wc(t_flags *arg, va_list ap);
void	ft_read_space(t_flags *arg);
void	ft_read_zero_minus(t_flags *arg);
bool	ft_redirect_fg(va_list ap, t_flags *arg);
void	ft_redirect_sp(va_list ap, t_flags *arg);
int		ft_set_flags(t_flags *arg, char *s, va_list ap);

#endif
