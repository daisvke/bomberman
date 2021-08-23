/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 03:31:37 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/23 05:43:29 by dtanigaw         ###   ########.fr       */
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

int		sl_render_buffer_with_colored_bloc(int **buffer, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < BLOC_LEN)
	{
		j = 0;
		while (j < BLOC_LEN)
		{
			buffer[i + y][j + x] = color;
			++j;
		}
		++i;
	}
	return (0);
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

void	sl_render_buffer_bloc_with_xpm(int **buffer, t_img *xpm_img, int x, int y)
{
	int	color;
	int	i;
	int	j;

	i = 0;
	while (i < BLOC_LEN)
	{
		j = 0;
		while (j < BLOC_LEN)
		{
			color = sl_get_color_from_img(xpm_img, j, i);
			buffer[i + y][j + x] = color;
			++j;
		}
		++i;
	}
}

void	sl_render_bloc_with_xpm(t_img *img, t_img *xpm_img, int x, int y, bool mask)
{
	int	color;
	int	i;
	int	j;

	i = 0;
	while (i < BLOC_LEN)
	{
		j = 0;
		while (j < BLOC_LEN)
		{
			color = sl_get_color_from_img(xpm_img, j, i);
			if (color >= 0)
				sl_img_pixel_put(img, j + x, i + y, color, mask);
			++j;
		}
		++i;
	}
}

void	sl_render_buffer_green_tile(t_env *env, int x, int y)
{
	int		**buffer;
	char	**map;

	buffer = env->buffer_bkgd;
	map = env->map;
	if (map[y - 1][x] == MAP_WALL)
		sl_render_buffer_bloc_with_xpm(buffer, &env->tex.tiles.tile_shadow, \
			BLOC_LEN * x, BLOC_LEN * y);
	else	
		sl_render_buffer_with_colored_bloc(buffer, GREEN_PXL, BLOC_LEN * x, BLOC_LEN * y);
}

void	sl_render_green_tile(t_env *env, t_dir curr_dir, int x, int y, int sub_x, int sub_y)
{
	t_img	*bkgd;
	char	**map;

	bkgd = &env->bkgd;
	map = env->map;
	if (sub_x != 0)
	{
		if (map[y][x] == MAP_ITEM_BOMB)
			sl_render_bloc_with_xpm(bkgd, &env->tex.bomb.item_bomb, \
				x * BLOC_LEN, y * BLOC_LEN, false);
		else if (map[y - 1][x] == MAP_WALL && curr_dir.down == false)
			sl_render_bloc_with_xpm(bkgd, &env->tex.tiles.tile_shadow, \
				sub_x, sub_y, false);
		else if	(map[y - 1][x] == MAP_WALL && curr_dir.down == true && sub_y == y * BLOC_LEN)
			sl_render_bloc_with_xpm(bkgd, &env->tex.tiles.tile_shadow, \
				sub_x, sub_y, false);
		else	
			sl_render_colored_bloc(bkgd, GREEN_PXL, sub_x, sub_y);
	}
}

void	sl_replace_with_green_tile(t_env *env, int x, int y)
{
	t_img	*bkgd;
	char	**map;
	int		map_x;
	int		map_y;

	bkgd = &env->bkgd;
	map = env->map;
	map_x = x / BLOC_LEN;
	map_y = y / BLOC_LEN;
	if (map[map_y][map_x] != MAP_WALL)
	{
		if (map[map_y - 1][map_x] == MAP_WALL)
			sl_render_bloc_with_xpm(bkgd, &env->tex.tiles.tile_shadow, \
				x, y, false);
		else	
			sl_render_colored_bloc(bkgd, GREEN_PXL, x, y);
	}
}

void	sl_render_background(t_env *env)
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
				sl_render_buffer_green_tile(env, j, i);
			else
				sl_render_buffer_bloc_with_xpm(env->buffer_bkgd, \
					&env->tex.wall, BLOC_LEN * j, BLOC_LEN * i);
			if (map[i][j] == MAP_ITEM_BOMB)
				sl_render_buffer_bloc_with_xpm(env->buffer_bkgd,\
					&env->tex.bomb.item_bomb, BLOC_LEN * j, BLOC_LEN * i);
			++j;
		}
		++i;
	}
}

void	sl_reveal_exit(t_env *env)
{
	t_pipe		exit;
	t_img		*curr_state;
	static int	i;

	exit = env->tex.exit_pipe;
	curr_state = NULL;
	if (i <= 80)
		curr_state = &exit.state0;
	if (i > 80 && i <= 160)
		curr_state = &exit.state1;
	if (i > 160 && i <= 240)
		curr_state = &exit.state2;
	if (i > 240 && i <= 320)
		curr_state = &exit.state3;
	if (i > 320)
		curr_state = &exit.state4;
	if (i == 400)
		curr_state = &exit.state5;
	else
		++i;
	sl_render_bloc_with_xpm(&env->bkgd, curr_state, exit.pos.x * BLOC_LEN, \
		exit.pos.y * BLOC_LEN, true);
}

void	sl_read_direction_and_animate_sprite(t_env *env, t_dir *dir, \
	t_sprite *sprite, int apply_to, t_img_patterns *img)
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
/*
void	sl_put_buffer_to_img(t_env *env)
{
	int	**buffer;
	int	color;
	int	i;
	int	j;

	buffer = env->buffer;
	i = 0;
	while (i < env->height * BLOC_LEN)
	{
		j = 0;
		while (j < env->width * BLOC_LEN)
		{
			color = buffer[i][j];
			if (color >= 0)
				sl_img_pixel_put(&env->bkgd, j, i, color, true);
			++j;
		}
		++i;
	}
}
*/
void	sl_put_buffer_bkgd_to_img(t_env *env)
{
	int	**buffer;
	int	color;
	int	i;
	int	j;

	buffer = env->buffer_bkgd;
	i = 0;
	while (i < env->height * BLOC_LEN)
	{
		j = 0;
		while (j < env->width * BLOC_LEN)
		{
			color = buffer[i][j];
			sl_img_pixel_put(&env->bkgd, j, i, color, false);
			++j;
		}
		++i;
	}
}

void	sl_init_canvas(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->height * BLOC_LEN)
	{
		j = 0;
		while (j < env->width * BLOC_LEN)
		{
			env->buffer[i][j] = 0;
			++j;
		}
		++i;
	}
}

void	sl_clear_sprites_last_positions(t_env *env)
{
	t_img		*bkgd;
	t_ennemies	ennemies;
	t_coord		p1_pos;
	t_coord		ennemy_pos;
	int			i;

	bkgd = &env->bkgd;
	p1_pos.x = env->p1.sub_pos.x;
	p1_pos.y = env->p1.sub_pos.y;
	sl_render_green_tile(env, env->p1.curr_dir, env->p1.pos.x, env->p1.pos.y, p1_pos.x, p1_pos.y); 
	ennemies = env->tex.ennemies;
	i = 0;
	while (i < ennemies.count) 
	{
		ennemy_pos.x = ennemies.sprites[i].sub_pos.x;
		ennemy_pos.y = ennemies.sprites[i].sub_pos.y;
		sl_render_green_tile(env, ennemies.sprites[i].curr_dir, ennemies.sprites[i].pos.x, \
			ennemies.sprites[i].pos.y, ennemy_pos.x, ennemy_pos.y);
		++i;
	}
	//clear bomb explosion
}

//put img to window (not render
int	sl_render(t_env *env)
{
	t_img	*img;
	t_img	*img2;
	static int	i;
	int	j;
	static int	k;
	static int	l;
	
//	sl_init_canvas(env);
//	sl_copy_bkgd_buffer_to_buffer(env);
//	env->buffer = env->buffer_bkgd;
	sl_clear_sprites_last_positions(env);
	if (env->p1.alive == true)
	{
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
		sl_render_bloc_with_xpm(&env->bkgd, img, env->p1.sub_pos.x, \
			env->p1.sub_pos.y, true);

		j = 0;
		t_ennemies	ennemies;
		ennemies = env->tex.ennemies;
		int	*time_death;
		while (j < ennemies.count) 
		{
			if (ennemies.sprites[j].alive == true)
			{
				img2 = env->tex.ennemies.sprites[j].curr_state;
				sl_render_bloc_with_xpm(&env->bkgd, img2, \
					ennemies.sprites[j].sub_pos.x, \
					ennemies.sprites[j].sub_pos.y, true);
			}
			else
			{
				time_death = env->tex.ennemies.sprites[j].time_death;
				if (time_death <= 1100)
				{
					sl_render_bloc_with_xpm(&env->bkgd, &ennemies.dead, \
						ennemies.sprites[j].sub_pos.x, \
						ennemies.sprites[j].sub_pos.y, true);
					++env->tex.ennemies.sprites[j].time_death;
				}
			}
			++j;
		}
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->bkgd.mlx_img, 0, 0);    
	}
	t_img		*death_state;
	static int	m = 0;
	
	death_state = NULL;
	if (env->p1.alive == false)
	{
		if (k <= CENTER_MESS_TIME * 3 + 200)
		{
			if (m <= 1000)
				death_state = &env->p1.img.dead.one;
			else if (m <= 2000)
				death_state = &env->p1.img.dead.two;
			else if (m <= 2200)
				death_state = &env->p1.img.dead.three;
			else if (m <= 2400)
				death_state = &env->p1.img.dead.four;
			else if (m <= 2600)
				death_state = &env->p1.img.dead.five;
			else if (m <= 2800)
				death_state = &env->p1.img.dead.six;
			else if (m <= 3000)
				death_state = &env->p1.img.dead.seven;
			else if (m <= 3200)
				death_state = &env->p1.img.dead.eight;
			sl_render_bloc_with_xpm(&env->bkgd, death_state, env->p1.sub_pos.x, \
				env->p1.sub_pos.y, true);
			mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->bkgd.mlx_img, 0, 0);    
			sl_put_centered_message_to_window(env, "GAME OVER !");
		}
		else
			sl_exit_game_over(env);
		++m;
		++k;
	}
	sl_put_counts_to_window(env);
	if (i <= CENTER_MESS_TIME)
	{
		sl_put_centered_message_to_window(env, "START !");
		++i;
	}
	return (0);
}
