/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc/so_long_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 05:40:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/16 05:43:56 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_STRUCTS_H
# define SO_LONG_STRUCTS_H

# include <stdbool.h>

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

typedef struct s_sprite
{
	bool			alive;
	int				time_death;
	t_img_patterns	img;
	void			*curr_state;
	int				curr_dir;
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
	bool	draw;
	t_coord	pos;
	int		explode_size;
	int		time1;
	int		time2;
	int		time3;
}			t_items;

typedef struct s_bombs
{
	t_img				item_bomb;
	int					to_collect;
	int					collected;
	t_items				item_bombs[ITEM_LIMIT];
	int					set_bombs_nbr;
	t_items				set_bombs[ITEM_LIMIT];
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
    t_sprite		sprites[ENNEMY_LIMIT];
}					t_ennemies;

typedef struct s_item
{
	t_img	img;
	int		to_collect;
	t_items	items[ITEM_LIMIT];
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
	t_img		canvas;
	int			width;
	int			height;
	char		**map;
	int			**buffer_bkgd;
	t_textures	tex;
	t_sprite	p1;
	t_img		icon_bomb;
	bool		errors[ERR_MAX];
	char		*stage_name;
	bool		game_clear;
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

#endif
