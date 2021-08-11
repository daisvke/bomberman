/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 03:31:37 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/11 05:09:49 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	sl_get_color_from_img(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

void	sl_img_pixel_put(t_img *img, int x , int y, int color, bool mask)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	if ((mask && color != GREEN_PXL) || !mask)
	{
		while (i >= 0)
		{
			if (img->endian)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

int		sl_render_colored_bloc(t_img *img, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < BLOC_LEN)
	{
		j = 0;
		while (j < BLOC_LEN)
		{
			sl_img_pixel_put(img, j + x, i + y, color, false);
			++j;
		}
		++i;
	}
	return (0);
}

void	sl_render_bloc_with_xpm(t_img *img, t_img *xpm_img, int x, int y)
{
	unsigned int	color;
	int	i;
	int	j;

	i = 0;
	while (i < BLOC_LEN)
	{
		j = 0;
		while (j < BLOC_LEN)
		{
			color = sl_get_color_from_img(xpm_img, j, i);
			sl_img_pixel_put(img, j + x, i + y, color, true);
			++j;
		}
		++i;
	}
}

void	sl_render_bkgd(t_env *env)
{
	char	**map;
	int		i;
	int		j;

	map = env->map;
	i = 0;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
		{
			if (map[i][j] != WALL)
				sl_render_colored_bloc(&env->bkgd, GREEN_PXL, BLOC_LEN * j, BLOC_LEN * i);
			else
				sl_render_bloc_with_xpm(&env->bkgd, &env->tex.wall,  BLOC_LEN * j,  BLOC_LEN * i);
			if (map[i][j] == ITEM_BOMB && map[env->p1.pos.y][env->p1.pos.x] != ITEM_BOMB)
				sl_render_bloc_with_xpm(&env->bkgd, &env->tex.bomb.item_bomb,  BLOC_LEN * j,  BLOC_LEN * i);
			++j;
		}
		++i;
	}
}

void	sl_handle_textures_while_moving(t_env *env, int delta_x, int delta_y)
{
	int	x;
	int	y;

	x = env->p1.pos.x + delta_x;
	y = env->p1.pos.y + delta_y;
	if (env->map[y][x] == ITEM_BOMB)
	{
		sl_render_colored_bloc(&env->bkgd, GREEN_PXL, BLOC_LEN * x, BLOC_LEN * y);
		env->map[y][x] = FLOOR;
		++env->tex.bomb.collected;
		if (env->tex.bomb.collected == env->tex.bomb.to_collect)
			env->tex.exit_pipe.appear = true;
	}
	// not bombs
	if (env->map[y][x] == MAP_EXIT && env->tex.exit_pipe.appear == true)
	{
		printf("GAME CLEAR\n");
		exit(EXIT_SUCCESS);
	}
}

void	sl_update_player_pos_on_map(t_env *env, int new_x, int new_y)
{
	char		**map;
	t_sprite	sprite;
	int			old_x;
	int			old_y;

	map = env->map;
	sprite = env->p1;
	old_x = sprite.pos.x;
	old_y = sprite.pos.y;
	map[old_y][old_x] = FLOOR;
}

void	sl_animate_sprite(t_env *env, t_sprite *sprite, t_states *img, bool *state, int x, int y)
{
	static int	i;
	char		**map;
	int			pos_x;
	int			pos_y;
	t_img		*curr_state;
	t_coord		bomb_pos;

	map = env->map;
	pos_x = sprite->pos.x + x;
	pos_y = sprite->pos.y + y;
	bomb_pos.x = env->tex.bomb.pos.x;
	bomb_pos.y = env->tex.bomb.pos.y;
	sl_update_player_pos_on_map(env, pos_x, pos_y);
	if (map[pos_y][pos_x] == WALL || (env->tex.bomb.set_bomb == true && (bomb_pos.x == pos_x && bomb_pos.y == pos_y)))
	{
		x = 0;
		y = 0;
	}
	sl_handle_textures_while_moving(env, x, y);
	map[sprite->pos.y + y][sprite->pos.x + x] = MAP_PLAYER;
	if (i <= 800)
	{
		sprite->curr_state = &img->two;
		sprite->sub_pos.x = sprite->pos.x * BLOC_LEN + x * (BLOC_LEN / 3);
		sprite->sub_pos.y = sprite->pos.y * BLOC_LEN + y * (BLOC_LEN / 3);
	}
	if (i > 800)
	{
		sprite->curr_state = &img->three;
		sprite->sub_pos.x = sprite->pos.x * BLOC_LEN + x * (2 * (BLOC_LEN / 3));
		sprite->sub_pos.y = sprite->pos.y * BLOC_LEN + y * (2 * (BLOC_LEN / 3));
	}
	if (i == 1600)
	{
		if (x != 0 || y != 0)
			++env->p1.moves;
		sprite->curr_state = &img->one;
		sprite->pos.x += x;
		sprite->pos.y += y;
		sprite->sub_pos.x = sprite->pos.x * BLOC_LEN;
		sprite->sub_pos.y = sprite->pos.y * BLOC_LEN;
		*state = false;
		i = 0;
	}
	else
		++i;
	curr_state = sprite->curr_state;
}

void	sl_reveal_exit(t_env *env)
{
	t_pipe		exit;
	t_img		*curr_state;
	static int	i;

	exit = env->tex.exit_pipe;
	curr_state = NULL;
	if (i <= 800)
		curr_state = &exit.state0;
	if (i > 800 && i <= 1600)
		curr_state = &exit.state1;
	if (i > 1600 && i <= 2400)
		curr_state = &exit.state2;
	if (i > 2400 && i <= 3200)
		curr_state = &exit.state3;
	if (i > 3200)
		curr_state = &exit.state4;
	if (i == 4000)
		curr_state = &exit.state5;
	else
		++i;
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, curr_state->mlx_img, exit.pos.x * BLOC_LEN, exit.pos.y * BLOC_LEN);
}

void	sl_check_if_sprite_is_dead(t_env *env, char *map[], int  x, int y)
{
	int	p1_x;
	int	p1_y;
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;

	p1_x = env->p1.pos.x;
	p1_y = env->p1.pos.y;
	x_start = x - 2;
	if (x_start < 0)
		x_start = 0;
	x_end = x + 2;
	if (x_start > env->width)
		x_end = env->width;
	y_start = y - 2;
	if (y_start < 0)
		y_start = 0;
	y_end = y + 2;
	if (y_start > env->width)
		y_end = env->width;
	while (x_start < x_end)
	{
		if (map[y][x_start] == MAP_PLAYER)
			sl_exit_game_over(env);
		if (map[y][x_start] == ITEM_BOMB)
		{
			sl_render_colored_bloc(&env->bkgd, GREEN_PXL, BLOC_LEN * x_start, BLOC_LEN * y);
			map[y][x_start] = FLOOR;
		}
		++x_start;
	}
	while (y_start < y_end)
	{
		if (map[y_start][x] == MAP_PLAYER)
			sl_exit_game_over(env);
		if (map[y_start][x] == ITEM_BOMB)
		{
			sl_render_colored_bloc(&env->bkgd, GREEN_PXL, BLOC_LEN * x, BLOC_LEN * y_start);
			map[y_start][x] = FLOOR;
		}
		++y_start;
	}
}

void	sl_explode_bomb(t_env *env, int x, int y, int *i, int *j)
{
	static int	k;

	if (k <= CENTER_MESS_TIME)
		sl_draw_segments_of_exploding_bomb(env, x, y);
	sl_check_if_sprite_is_dead(env, env->map, x / BLOC_LEN, y / BLOC_LEN);
	++k;
	if (k > CENTER_MESS_TIME + 50)
	{
		*i = 0;
		*j = 0;
		k = 0;
		env->tex.bomb.set_bomb = false;
	}
}

void    sl_set_bomb(t_env *env)
{
    static int	i;
	static int	j;
	int			bomb_pos_x;
	int			bomb_pos_y;
	t_states	set_bomb;		

	set_bomb = env->tex.bomb.set_states;
	bomb_pos_x = env->tex.bomb.pos.x * BLOC_LEN;
	bomb_pos_y = env->tex.bomb.pos.y * BLOC_LEN;
    if (i <= 12800)
    {
        if (i % 3200 == 0)
			++j;
		if (j % 2 == 0)
		{
		//	sl_render_bloc_with_xpm(&env->bkgd, &set_bomb.one, bomb_pos_x, bomb_pos_y);
			mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, set_bomb.one.mlx_img, bomb_pos_x, bomb_pos_y);
		//	env->tex.bomb.curr_state = &set_bomb.one;
		}
		else
		{
		//	sl_render_bloc_with_xpm(&env->bkgd, &set_bomb.three, bomb_pos_x, bomb_pos_y);
			mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, set_bomb.three.mlx_img, bomb_pos_x, bomb_pos_y);
		//	env->tex.bomb.curr_state = &set_bomb.three;
		}
        ++i;
    }
	if (i > 12800)
		sl_explode_bomb(env, bomb_pos_x, bomb_pos_y, &i, &j);
}
/*
void	sl_overlay_bomb_and_player(t_env *env)
{
	t_img	*bomb_curr_state;
	t_img	*player_curr_state;
	unsigned int	color;
	int	i;
	int	j;
	int			bomb_pos_x;
	int			bomb_pos_y;

	bomb_pos_x = env->tex.bomb.pos.x * BLOC_LEN;
	bomb_pos_y = env->tex.bomb.pos.y * BLOC_LEN;

	bomb_curr_state = env->tex.bomb.curr_state;
//	bomb_curr_state = &env->tex.bomb.set_states.three;
	player_curr_state = env->p1.curr_state;
	if (env->p1.pos.x == env->tex.bomb.pos.x && env->p1.pos.y == env->tex.bomb.pos.y)
		sl_render_bloc_with_xpm(&env->tex.bomb.set_states.one, player_curr_state, 0, 0);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, bomb_curr_state->mlx_img, bomb_pos_x, bomb_pos_y);
}
*/
//put img to window (not render
int	sl_render(t_env *env)
{
	t_img	*img;
	static int	i;
	
	int			bomb_pos_x;
	int			bomb_pos_y;

	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->bkgd.mlx_img, 0, 0);    
	if (env->p1.curr_dir.up)
		sl_animate_sprite(env, &env->p1, &env->p1.img.up, &env->p1.curr_dir.up, 0, UP);
	if (env->p1.curr_dir.down)
		sl_animate_sprite(env, &env->p1, &env->p1.img.down, &env->p1.curr_dir.down, 0, DOWN);
	if (env->p1.curr_dir.left)
		sl_animate_sprite(env, &env->p1, &env->p1.img.left, &env->p1.curr_dir.left, LEFT, 0);
	if (env->p1.curr_dir.right)
		sl_animate_sprite(env, &env->p1, &env->p1.img.right, &env->p1.curr_dir.right, RIGHT, 0);
	if (env->tex.exit_pipe.appear == true)
		sl_reveal_exit(env);
	if (env->tex.bomb.set_bomb == true)
	{
		sl_set_bomb(env);
	//	sl_overlay_bomb_and_player(env);
	}
//	if (!(env->p1.pos.x == env->tex.bomb.pos.x && env->p1.pos.y == env->tex.bomb.pos.y))
//	{
		img = env->p1.curr_state;
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, img->mlx_img, env->p1.sub_pos.x, env->p1.sub_pos.y);
//	}
//	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->bkgd.mlx_img, 0, 0);    
	sl_put_move_count_to_window(env);
	if (i <= CENTER_MESS_TIME)
	{
		sl_put_centered_message_to_window(env, "START !");
		++i;
	}
	return (0);
}
