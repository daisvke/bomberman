/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:19:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/24 06:18:56 by dtanigaw         ###   ########.fr       */
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
# define MAP_ELEMS			"01CEPM"
# define MAP_COLLECTIBLES	"BFS"

# define MAP_FLOOR			'0'
# define MAP_WALL			'1'
# define MAP_ITEM_BOMB		'B'
# define MAP_FIRE			'F'
# define MAP_SPEED			'S'
# define MAP_EXIT			'3'
# define MAP_PLAYER			'4'
# define MAP_ENNEMY			'5'

# define UP					-1
# define DOWN				1
# define LEFT				-1
# define RIGHT				1

/*
** parsing
*/
# define ERROR				-1
# define COLLECTIBLE		2
# define EXIT				3
# define PLAYER				4
# define ENNEMY             5

/*
** colors
*/
# define GREEN_PXL			0x107830

/*
**	write to window 
*/
# define CENTER_MESS_TIME	1000

/*
** determine ennemy position
*/
# define UP_LEN				0
# define DOWN_LEN			1
# define LEFT_LEN			2
# define RIGHT_LEN			3
# define KEEP				1

typedef struct s_coord
{
	int	x;
	int	y;
}		t_coord;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_pipe
{
	bool	appear;
	t_img	state0;
	t_img	state1;
	t_img	state2;
	t_img	state3;
	t_img	state4;
	t_img	state5;
	t_coord	pos;
}			t_pipe;

typedef struct s_states
{
	t_img	one;
	t_img	two;
	t_img	three;
}			t_states;

typedef struct s_dead
{
	t_img	one;
	t_img	two;
	t_img	three;
	t_img	four;
	t_img	five;
	t_img	six;
	t_img	seven;
	t_img	eight;
}			t_dead;

typedef struct s_img_patterns
{
	t_states	up;
	t_states	down;
	t_states	left;
	t_states	right;
	t_dead		dead;
}				t_img_patterns;

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
	bool			alive;
	int				time_death;
	t_img_patterns	img;
	void			*curr_state;
	t_dir			curr_dir;
	t_coord			pos;
	t_coord			sub_pos;
	int				speed;
	int				time;
	int				moves;
	t_img			icon;
}					t_sprite;

typedef struct s_explode_states
{
	t_img		ctr;
	t_states	hrz;
	t_states	vrt;
}				t_explode_states;

typedef struct s_items
{
	t_coord	pos;
	bool	draw;
}			t_items;

typedef struct s_bombs
{
	t_img				item_bomb;
	int					to_collect;
	int					collected;
	t_items				item_bombs[50];
	bool				set_bomb;
	t_coord				pos;
	t_states			set_states;
	void				*curr_state;
	t_explode_states	explode_states;
	int					explode_size;
}						t_bombs;

typedef struct s_ennemies
{
    t_img_patterns 	img;
	t_img			dead;
	int				count;
    t_sprite		sprites[50];
}					t_ennemies;

typedef struct s_item
{
	t_img	img;
	int		to_collect;
	t_items	items[50];
}			t_item;

typedef struct s_tiles
{
	t_img	tile;
	t_img	tile_shadow;
}			t_tiles;

typedef struct s_textures
{
	t_img	    wall;
	t_tiles		tiles;
	t_bombs	    bomb;
	t_item		fire;
	t_item		speed;
	t_pipe	    exit_pipe;
    t_ennemies  ennemies;
}				t_textures;

typedef struct s_env
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		bkgd;
	int			width;
	int			height;
	bool		keypress;
	char		**map;
	int			**buffer_bkgd;
	int			**buffer;
	t_textures	tex;
	t_sprite	p1;
	t_img		icon_bomb;
}				t_env;

typedef struct s_square
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}		t_square;

typedef struct s_count
{
    int player;
	int	collectible;
    int exit_pipe;
}		t_count;

/*
** init
*/
void	sl_init_buffers(t_env *env);
void	sl_init_env(t_env *env);
void	sl_init_sprite(t_sprite *sprite, int x, int y, int speed);

/*
** parse
*/
void	sl_parse_map(t_env *data, char *filename);

/*
** put to window
*/
void	sl_put_move_count_to_window(t_env *env);
void	sl_put_centered_message_to_window(t_env *env, char *message);

/*
** render
*/
void	sl_img_pixel_put(t_img *img, int x , int y, int color, bool mask);
int		sl_render(t_env *data);
void	sl_render_background(t_env *data);
int		sl_render_colored_bloc(t_img *img, int color, int x, int y);

/*
** texture interactions
*/
void	sl_find_and_turn_off_item(t_items *items, int max, int x, int y);

/*
** animate sprites
*/
int	sl_is_collectible(char elem_to_check);

int    sl_exit_game(t_env *env, char *err_mess);

/*
** bomb
*/
void    sl_set_bomb(t_env *env);

#endif
