/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 03:31:37 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/17 23:15:04 by dtanigaw         ###   ########.fr       */
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
			if (map[i][j] != MAP_WALL)
				sl_render_colored_bloc(&env->bkgd, GREEN_PXL, BLOC_LEN * j, BLOC_LEN * i);
			else
				sl_render_bloc_with_xpm(&env->bkgd, &env->tex.wall,  BLOC_LEN * j,  BLOC_LEN * i);
			if (map[i][j] == MAP_ITEM_BOMB && map[env->p1.pos.y][env->p1.pos.x] != MAP_ITEM_BOMB)
				sl_render_bloc_with_xpm(&env->bkgd, &env->tex.bomb.item_bomb,  BLOC_LEN * j,  BLOC_LEN * i);
			++j;
		}
		++i;
	}
}

void	sl_put_back_exit_on_map(t_env *env)
{
	char	**map;
	int		x;
	int		y;

	map = env->map;
	x = env->tex.exit_pipe.pos.x;
	y = env->tex.exit_pipe.pos.y;
	map[y][x] = MAP_EXIT;
}

void	sl_update_player_pos_on_map(t_env *env, int apply_to, \
	t_sprite *sprite, int x, int y)
{
	char	**map;
	int		old_x;
	int		old_y;
	int		new_x;
	int		new_y;

	map = env->map;
	old_x = sprite->pos.x;
	old_y = sprite->pos.y;
	new_x = sprite->pos.x + x;
	new_y = sprite->pos.y + y;
	if (!(apply_to == ENNEMY && (map[old_y][old_x] == MAP_ITEM_BOMB)))
		map[old_y][old_x] = MAP_FLOOR;
	if (apply_to == PLAYER)
		map[sprite->pos.y + y][sprite->pos.x + x] = MAP_PLAYER;
	else if (apply_to == ENNEMY && map[new_y][new_x] != MAP_ITEM_BOMB)
		map[new_y][new_x] = MAP_ENNEMY;
	sl_put_back_exit_on_map(env);
}

void	sl_animate_sprite(t_env *env, t_sprite *sprite, int apply_to, t_states *img, bool *state, int x, int y)
{
	static int	i;
	char		**map;
	int			pos_x;
	int			pos_y;
	t_coord		bomb_pos;

	map = env->map;
	pos_x = sprite->pos.x + x;
	pos_y = sprite->pos.y + y;
	bomb_pos.x = env->tex.bomb.pos.x;
	bomb_pos.y = env->tex.bomb.pos.y;
	if (map[pos_y][pos_x] == MAP_WALL || (env->tex.bomb.set_bomb == true && (bomb_pos.x == pos_x && bomb_pos.y == pos_y)))
	{
		x = 0;
		y = 0;
	}
	sl_handle_textures_while_moving(env, apply_to, x, y);
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
		if (apply_to == PLAYER && (x != 0 || y != 0))
			++env->p1.moves;
		sprite->curr_state = &img->one;
		sl_update_player_pos_on_map(env, apply_to, sprite, x, y);
		sprite->pos.x += x;
		sprite->pos.y += y;
		sprite->sub_pos.x = sprite->pos.x * BLOC_LEN;
		sprite->sub_pos.y = sprite->pos.y * BLOC_LEN;
		if (apply_to != ENNEMY)
			*state = false;
		i = 0;
	}
	else
		++i;
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

void	sl_read_direction_and_animate_sprite(t_env *env, t_dir *dir, t_sprite *sprite, int apply_to, t_img_patterns *img)
{
	if (dir->up)
		sl_animate_sprite(env, sprite, apply_to, &img->up, &dir->up, 0, UP);
	if (dir->down)
		sl_animate_sprite(env, sprite, apply_to, &img->down, &dir->down, 0, DOWN);
	if (dir->left)
		sl_animate_sprite(env, sprite, apply_to, &img->left, &dir->left, LEFT, 0);
	if (dir->right)
		sl_animate_sprite(env, sprite, apply_to, &img->right, &dir->right, RIGHT, 0);
}

//put img to window (not render
int	sl_render(t_env *env)
{
	t_img	*img;
	t_img	*img2;
	static int	i;
	
	int	j;
	int			bomb_pos_x;
	int			bomb_pos_y;

	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->bkgd.mlx_img, 0, 0);    
	sl_read_direction_and_animate_sprite(env, &env->p1.curr_dir, &env->p1, PLAYER, &env->p1.img);
	sl_read_and_animate_ennemies(env);
	if (env->tex.exit_pipe.appear == true)
		sl_reveal_exit(env);
	if (env->tex.bomb.set_bomb == true)
	{
		sl_set_bomb(env);
	//	sl_overlay_bomb_and_player(env);
	}
	img = env->p1.curr_state;
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, img->mlx_img, env->p1.sub_pos.x, env->p1.sub_pos.y);
	j = 0;
	t_ennemies	ennemies;
	ennemies = env->tex.ennemies;

	while (j < ennemies.count) 
	{
		if (ennemies.sprites[j].alive == true)
		{
			img2 = env->tex.ennemies.sprites[j].curr_state;
			mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, img2->mlx_img, ennemies.sprites[j].sub_pos.x, ennemies.sprites[j].sub_pos.y);
		}
		++j;
	}
	sl_put_move_count_to_window(env);
	if (i <= CENTER_MESS_TIME)
	{
		sl_put_centered_message_to_window(env, "START !");
		++i;
	}
	return (0);
}
