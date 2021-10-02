/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_to_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:56:27 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/02 16:19:12 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	sl_put_colored_str_to_terminal(char *str, char *color)
{
	sl_put_str_to_terminal(color);
	sl_put_str_to_terminal("\t\t");
	sl_put_str_to_terminal(str);
	sl_put_str_to_terminal(STR_WHITE);
	sl_put_str_to_terminal("\n\n");
}

void	sl_put_str_to_terminal(char *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
}

void	sl_put_nbr_to_terminal(int nbr)
{
	int	nbr_in_char;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr < 10)
	{
		nbr_in_char = nbr + '0';
		write(STDIN_FILENO, &nbr_in_char, 1);
	}
	else if (nbr > 9)
	{
		sl_put_nbr_to_terminal(nbr / 10);
		sl_put_nbr_to_terminal(nbr % 10);
	}
}

void	sl_put_steps_on_terminal(t_env *env)
{
	sl_put_str_to_terminal("> Steps:\t\t");
	sl_put_nbr_to_terminal(env->p1.moves);
	sl_put_str_to_terminal("\n\n");
}
