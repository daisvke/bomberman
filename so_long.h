/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:19:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/05 06:07:54 by dtanigaw         ###   ########.fr       */
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

# include "libft/libft.h"

# define FILE_EXTENSION		".ber"
# define FILE_EXTENSION_LEN	3

# define BLOC_LEN			24
# define MAP_ELEMS			"01CEP"

# define WALL				'1'
# define ITEM_BOMB			'2'

# define UP					-1
# define DOWN				1
# define LEFT				-1
# define RIGHT				1

/*
** parsing
*/
# define ERROR				-1
# define BOMB				2
# define PLAYER				4

/*
** colors
*/
# define GREEN_PXL	0x107830

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_exit
{
	bool	appear;
	t_img	img;
}			t_exit;

typedef struct s_dlr
{
	t_img	def;
	t_img	l;
	t_img	r;
}			t_dlr;

typedef struct s_img_patterns
{
	t_dlr	up;
	t_dlr	down;
	t_dlr	left;
	t_dlr	right;
}			t_img_patterns;

typedef struct s_coord
{
	int	x;
	int	y;
}		t_coord;

// try bitshift
typedef struct s_dir
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}			t_dir;

typedef struct s_sprite
{
	t_img_patterns	img;
	void			*curr_state;
	t_dir			curr_dir;
	t_coord			pos;
	t_coord			sub_pos;
}					t_sprite;

typedef struct s_bombs
{
	t_img	item_bomb;
	int		to_collect;
	int		collected;
}		t_bombs;

typedef struct s_textures
{
	t_img	wall;
	t_bombs	bomb;
	t_exit	exit;
}			t_textures;

typedef struct s_env
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		bkgd;
	int			width;
	int			height;
	char		**map;
	t_textures	tex;
	t_sprite	p1;
}			t_env;

typedef struct s_square
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}		t_square;

/*
** parse
*/
void	sl_parse_map(t_env *data, char *filename);

/*
** render
*/
void	sl_img_pixel_put(t_img *img, int x, int y, int color);
int		sl_render(t_env *data);
void	sl_render_background(t_env *data);
int		sl_render_colored_bloc(t_img *img, int color, int x, int y);

#endif
