/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:19:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/16 01:49:08 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <X11/X.h>

# define WINDOW_WIDTH	600
# define WINDOW_HEIGHT	300

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_data;

#endif
