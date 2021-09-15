/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:19:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/15 14:28:54 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* DEL !!!  */
# include <stdio.h>

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <X11/X.h>


/*
** get_next_line
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define ERROR2 -2
# define REACHED_EOF 0
# define LINE_READ 1

/*
** string colors
*/
# define STR_RED			"\033[31m"
# define STR_WHITE			"\033[0m"

# define FILE_EXTENSION		".ber"
# define FILE_EXTENSION_LEN	3
# define SAME				0

# define ERR_MAX			23

# define BLOC_LEN			24
# define MAP_ELEMS			"01CEPM"
# define MAP_COLLECTIBLES	"BFS"

# define ENNEMY_LIMIT		15
# define ITEM_LIMIT			30

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
** current direction
*/
# define CR_UP				8
# define CR_DOWN			4
# define CR_LEFT			2
# define CR_RIGHT			1

# define NO_AVAILABLE_SLOT	-1

/*
** parsing
*/
# define SUCCESS			0
# define ERROR				-1
# define COLLECTIBLE		2
# define EXIT				3
# define PLAYER				4
# define ENNEMY             5

/*
** colors
*/
# define WHITE			0xFFFFFF
# define GREEN			0x107830

/*
**	write to window 
*/
# define CENTER_MESS_TIME	1000

/*
** speeds
*/
# define PLAYER_SPEED		170
# define ENNEMY_SPEED		340
# define BOMB_SET_TIME		2280
# define BOMB_EXPLODE_TIME	1000
# define REVEAL_EXIT_SPEED	30

/*
** determine ennemy position
*/
# define UP_LEN				0
# define DOWN_LEN			1
# define LEFT_LEN			2
# define RIGHT_LEN			3
# define KEEP				1
# define FOUND_PLAYER		1

/*
** bombs
*/
# define START_BOMB			1

/*
** death
*/
# define PLAYER_DEATH_TIME	1000
# define ENNEMY_DEATH_TIME	1100

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
	bool			stop;
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
** system calls
*/
void	ft_close(t_env *env, int fd);
void	*ft_free(void *ptr);
void	*ft_malloc(t_env *env, size_t num, size_t size);
int		ft_open(t_env *env, char *filename);

/*
** utils
*/
t_coord	sl_assign_pos(int x, int y);
char	*ft_itoa(t_env *env, int n);
char    *ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);

/*
** init
*/
void	sl_check_errors_1(t_env *env);
void	sl_init_array(int *array, size_t size);
t_count	sl_init_counter(void);
void	sl_init_buffers(t_env *env);
void	sl_init_errors(t_env *env);
void	sl_init_mlx(t_env *env, int width, int height);
void	sl_init_set_bomb(t_items *bomb, bool draw, int x, int y, int size);
void	sl_init_sprite(t_sprite *sprite, int x, int y, int speed);

/*
** load textures
*/
void	sl_load_ennemies(t_env *env);
void	sl_load_ennemies_horizontal(t_env *env);
void	sl_load_ennemies_vertical(t_env *env);
void	sl_load_exit(t_env *env);
void	sl_load_white_bomber(t_env *env);

void	sl_handle_keypress_bb(int keycode, t_env *env);
/*
** keypress
*/
int		sl_handle_keypress(int keycode, t_env *env);
int		sl_handle_keyrelease(int keycode, t_env *env);

/*
** parsing
*/
void	sl_assign_collectible_type_randomly(t_env *env, t_coord pos, int *count);
void    sl_check_counter(t_env *env, t_count counter);
void	sl_check_errors_2(t_env *env, int res);
void	sl_parse_map(t_env *data, char *filename);

/*
** put to window
*/
void	sl_put_message_at_start(t_env *env);
void	sl_put_move_count_to_window(t_env *env);
void	sl_put_centered_message_to_window(t_env *env, char *message);
void	sl_put_counts_to_window(t_env *env);
void	sl_put_stage_name(t_env *env);

/*
** render
*/
void	sl_draw_collectibles(t_env *env);
void	sl_draw_collectibles_by_category(t_env *env, t_items *items, \
	t_img *img, int max);
int		sl_get_color_from_img(t_img *img, int x, int y);
void	sl_img_pixel_put(t_img *img, int x, int y, int color, bool mask);
int		sl_render(t_env *data);
void	sl_render_background(t_env *data);
void	sl_render_bloc_with_xpm(t_img *img, t_img *xpm_img, t_coord pos, bool mask);
void	sl_render_bombs(t_env *env);
void	sl_render_buffer_bloc_with_xpm(int **buffer, t_img *xpm_img, t_coord pos);
void	sl_render_buffer_green_tile(t_env *env, t_coord pos);
int		sl_render_buffer_with_colored_bloc(int **buffer, int color, t_coord pos);
int		sl_render_colored_bloc(t_img *img, int color, t_coord pos);
void	sl_render_ennemies(t_env *env);
void	sl_render_green_tile_by_direction(t_env *env, int curr_dir, t_coord pos);
void	sl_render_p1(t_env *env);
void	sl_replace_with_green_tile(t_env *env, t_coord pos);

/*
** texture interactions
*/
void	sl_find_and_turn_off_item(t_items *items, int max, int x, int y);
void	sl_handle_textures_while_moving(t_env *env, int apply_to, t_coord delta);

/*
** animate sprites
*/
void	sl_animate_sprite(t_env *env, t_sprite *sprite, int apply_to, t_states *img, t_coord coord); 
int		sl_is_collectible(char elem_to_check);

/*
** update position
*/
void	sl_update_player_pos_on_map(t_env *env, int apply_to, t_sprite *sprite, int x, int y);
void	sl_update_sub_pos(t_sprite *sprite, t_img *img, t_coord delta);
void	sl_update_sub_pos_state_0(t_sprite *sprite, t_states *img, t_coord pos);
void	sl_update_sub_pos_state_1(t_sprite *sprite, t_states *img, t_coord pos);
void	sl_update_sub_pos_state_2(t_env *env, t_sprite *sprite, int apply_to, t_states *img, t_coord coord);

/*
** bomb
*/
void	sl_clear_segments_of_exploding_bomb(t_env *env, t_items *bomb, t_coord pos);
void	sl_draw_segments_of_exploding_bomb(t_env *env, t_items *bomb, t_coord pos);
void    sl_set_bomb(t_env *env, t_items *bomb);

/*
** death
*/
void	sl_kill_ennemy(t_env *env, t_sprite *ennemy);
void	sl_kill_p1(t_env *env);

/*
** exit game
*/
int    sl_exit_game(t_env *env);
void	sl_put_err_code_and_exit_game(t_env *env, int err_code);



/*
** gnl
*/

char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strsdup(char *src, int size);
char	*ft_gnl_substr(char *s, size_t start, size_t len);

#endif
