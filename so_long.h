/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:19:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/02 14:09:05 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <X11/X.h>

# define BLOC_PXL_LEN	24
# define MAP_ELEMS		"01CEP"

# define WALL			'1'
# define ITEM_BOMB		'2'

/*
** parsing
*/
# define BOMB			2
# define PLAYER			4

/*
** colors
*/
# define GREEN_PIXEL	0x107830

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
}			t_img;

typedef struct s_exit
{
	bool	appear;
	t_img	img;
}			t_exit;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_img	player;
	t_img	wall;
	t_img	item_bomb;
	t_exit	exit;
	int		bombs_to_collect;
	int		collected_bombs;
	int		width;
	int		height;
	char	**map;
}			t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}		t_rect;

/*
** parse
*/
void	sl_parse_map(t_data *data, char *filename);

/*
** render
*/
void	sl_img_pixel_put(t_img *img, int x, int y, int color);
int		sl_render(t_data *data);
void	sl_render_background(t_data *data);
int		sl_render_colored_bloc(t_img *img, int color, int x, int y);

#endif
