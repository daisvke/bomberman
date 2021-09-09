/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 03:31:37 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/09 04:27:31 by dtanigaw         ###   ########.fr       */
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

void	sl_render_green_tile(t_env *env, int curr_dir, int pos_x, int pos_y)
{
	t_img	*bkgd;
	char	**map;
	int		x;
	int		y;

	x = pos_x / BLOC_LEN;
	y = pos_y / BLOC_LEN;
	bkgd = &env->canvas;
	map = env->map;
	if (map[y - 1][x] == MAP_WALL && !(curr_dir & CR_DOWN))
		sl_render_bloc_with_xpm(bkgd, &env->tex.tiles.tile_shadow, \
			pos_x, pos_y, false);
	else if	(map[y - 1][x] == MAP_WALL && (curr_dir & CR_DOWN))
		sl_render_bloc_with_xpm(bkgd, &env->tex.tiles.tile_shadow, \
			pos_x, pos_y, false);
	else	
		sl_render_colored_bloc(bkgd, GREEN_PXL, pos_x, pos_y);
	if ((curr_dir & CR_UP) && map[y - 1][x] != MAP_WALL)
	{
		if (map[y - 2][x] == MAP_WALL)
			sl_render_bloc_with_xpm(bkgd, &env->tex.tiles.tile_shadow, \
				pos_x, pos_y - BLOC_LEN, false);
		else
			sl_render_colored_bloc(bkgd, GREEN_PXL, pos_x, pos_y - BLOC_LEN);
	}
	if ((curr_dir & CR_DOWN) && map[y + 1][x] != MAP_WALL)
		sl_render_colored_bloc(bkgd, GREEN_PXL, pos_x, pos_y + BLOC_LEN);
	if ((curr_dir & CR_LEFT) && map[y][x - 1] != MAP_WALL)
	{
		if (map[y - 1][x - 1] == MAP_WALL)
			sl_render_bloc_with_xpm(bkgd, &env->tex.tiles.tile_shadow, \
				pos_x - BLOC_LEN, pos_y, false);
		else
			sl_render_colored_bloc(bkgd, GREEN_PXL, pos_x - BLOC_LEN, pos_y);
	}
	if ((curr_dir & CR_RIGHT) && map[y][x + 1] != MAP_WALL)
	{
		if (map[y - 1][x + 1] == MAP_WALL)
			sl_render_bloc_with_xpm(bkgd, &env->tex.tiles.tile_shadow, \
				pos_x + BLOC_LEN, pos_y, false);
		else
			sl_render_colored_bloc(bkgd, GREEN_PXL, pos_x + BLOC_LEN, pos_y);
	}
}

void	sl_replace_with_green_tile(t_env *env, int x, int y)
{
	t_img	*bkgd;
	char	**map;
	int		map_x;
	int		map_y;

	bkgd = &env->canvas;
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
			++j;
		}
		++i;
	}
}

void	sl_reveal_exit(t_env *env)
{
	t_pipe		exit;
	t_img		*curr_state;
	static int	time;

	exit = env->tex.exit_pipe;
	curr_state = NULL;
	if (time <= REVEAL_EXIT_SPEED)
		curr_state = &exit.state0;
	else if (time <= REVEAL_EXIT_SPEED * 2)
		curr_state = &exit.state1;
	else if (time <= REVEAL_EXIT_SPEED * 3)
		curr_state = &exit.state2;
	else if (time <= REVEAL_EXIT_SPEED * 4)
		curr_state = &exit.state3;
	else if (time < REVEAL_EXIT_SPEED * 5)
		curr_state = &exit.state4;
	if (time == REVEAL_EXIT_SPEED * 5)
		curr_state = &exit.state5;
	else
		++time;
	sl_render_bloc_with_xpm(&env->canvas, curr_state, exit.pos.x * BLOC_LEN, \
		exit.pos.y * BLOC_LEN, true);
}

void	sl_read_direction_and_animate_sprite(t_env *env, t_sprite *sprite, \
	int apply_to, t_img_patterns *img)
{
	t_coord	pos;
	int		dir;

	dir = sprite->curr_dir;
	if (dir & CR_UP)
	{
		pos = sl_assign_pos(0, UP);
		sl_animate_sprite(env, sprite, apply_to, &img->up, pos);
	}
	if (dir & CR_DOWN)
	{
		pos = sl_assign_pos(0, DOWN);
		sl_animate_sprite(env, sprite, apply_to, &img->down, pos);
	}
	if (dir & CR_LEFT)
	{
		pos = sl_assign_pos(LEFT, 0);
		sl_animate_sprite(env, sprite, apply_to, &img->left, pos);
	}
	if (dir & CR_RIGHT)
	{
		pos = sl_assign_pos(RIGHT, 0);
		sl_animate_sprite(env, sprite, apply_to, &img->right, pos);
	}
}

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
			sl_img_pixel_put(&env->canvas, j, i, color, false);
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

	bkgd = &env->canvas;
	p1_pos = sl_assign_pos(env->p1.pos.x * BLOC_LEN, env->p1.pos.y * BLOC_LEN);
	sl_render_green_tile(env, env->p1.curr_dir, p1_pos.x, p1_pos.y); 
	ennemies = env->tex.ennemies;
	i = 0;
	while (i < ennemies.count) 
	{
		ennemy_pos.x = ennemies.sprites[i].pos.x * BLOC_LEN;
		ennemy_pos.y = ennemies.sprites[i].pos.y * BLOC_LEN;
		sl_render_green_tile(env, ennemies.sprites[i].curr_dir, ennemy_pos.x, ennemy_pos.y);
		++i;
	}
}

void	sl_draw_collectibles_by_category(t_env *env, t_items *items, \
	t_img *img, int max)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < max)
	{
		x = items[i].pos.x * BLOC_LEN;
		y = items[i].pos.y * BLOC_LEN;
		if (items[i].draw == true)
			sl_render_bloc_with_xpm(&env->canvas, img, x, y, true);
		else
			sl_replace_with_green_tile(env, x, y);
		++i;
	}
}

void	sl_draw_collectibles(t_env *env)
{
	sl_draw_collectibles_by_category(env, env->tex.bomb.item_bombs, \
		&env->tex.bomb.item_bomb, env->tex.bomb.to_collect);
	sl_draw_collectibles_by_category(env, env->tex.fire.items, \
		&env->tex.fire.img, env->tex.fire.to_collect);
	sl_draw_collectibles_by_category(env, env->tex.speed.items, \
		&env->tex.speed.img, env->tex.speed.to_collect);
}

void	sl_render_p1(t_env *env)
{
	t_img_patterns	p1_img;
	t_img			*img;
	t_coord			pos;

	p1_img = env->p1.img;
	sl_read_direction_and_animate_sprite(env, &env->p1, PLAYER, &p1_img);
	sl_read_and_animate_ennemies(env);
	img = env->p1.curr_state;
	pos = sl_assign_pos(env->p1.sub_pos.x, env->p1.sub_pos.y);
	sl_render_bloc_with_xpm(&env->canvas, img, pos.x, pos.y, true);
}

void	sl_render_bombs(t_env *env)
{
	int 	i;
	
	i = 0;
	if (env->tex.bomb.set_bombs_nbr > 0)
	{
		while (i < env->tex.bomb.collected)
		{
			if (env->tex.bomb.set_bombs[i].draw == true)
				sl_set_bomb(env, &env->tex.bomb.set_bombs[i]);
			++i;
		}
	}
}

void	sl_kill_ennemy(t_env *env, t_sprite *ennemy)
{
	t_ennemies	ennemies;
	t_coord		pos;
	int			*time_death;

	ennemies = env->tex.ennemies;
	pos = sl_assign_pos(ennemy->sub_pos.x, ennemy->sub_pos.y);
	time_death = &ennemy->time_death;
	if (*time_death <= 1100)
	{
		sl_render_bloc_with_xpm(&env->canvas, &ennemies.dead, pos.x, pos.y, true);
		++ennemy->time_death;
	}
}

void	sl_render_ennemies(t_env *env)
{
	t_ennemies	ennemies;
	t_img		*img;
	int			i;

	ennemies = env->tex.ennemies;
	i = 0;
	while (i < ennemies.count) 
	{
		if (ennemies.sprites[i].alive == true)
		{
			img = env->tex.ennemies.sprites[i].curr_state;
			sl_render_bloc_with_xpm(&env->canvas, img, \
				ennemies.sprites[i].sub_pos.x, \
				ennemies.sprites[i].sub_pos.y, true);
		}
		else
			sl_kill_ennemy(env, &env->tex.ennemies.sprites[i]);
		++i;
	}
}

t_img	*sl_get_death_state(t_env *env, int time)
{
	t_img	*death_state;

	death_state = NULL;
	if (time <= CENTER_MESS_TIME / 4)
		death_state = &env->p1.img.dead.one;
	else if (time <= CENTER_MESS_TIME / 3.5)
		death_state = &env->p1.img.dead.two;
	else if (time <= CENTER_MESS_TIME / 2.7)
		death_state = &env->p1.img.dead.three;
	else if (time <= CENTER_MESS_TIME / 2.3)
		death_state = &env->p1.img.dead.four;
	else if (time <= CENTER_MESS_TIME / 2)
		death_state = &env->p1.img.dead.five;
	else if (time <= CENTER_MESS_TIME / 1.6)
		death_state = &env->p1.img.dead.six;
	else if (time <= CENTER_MESS_TIME / 1.3)
		death_state = &env->p1.img.dead.seven;
	else
		death_state = &env->p1.img.dead.eight;
	return (death_state);
}

void	sl_kill_p1(t_env *env)
{
	t_img		*death_state;
	static int	time;
	
	death_state = NULL;
	if (time <= CENTER_MESS_TIME)
	{
		death_state = sl_get_death_state(env, time);
		sl_render_bloc_with_xpm(&env->canvas, death_state, env->p1.sub_pos.x, env->p1.sub_pos.y, true);
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, \
			env->canvas.mlx_img, 0, 0);    
		sl_put_centered_message_to_window(env, "GAME OVER !");
	}
	else
		sl_exit_game_over(env);
	++time;
}

int	sl_render(t_env *env)
{
	void	*mlx_img;

	sl_clear_sprites_last_positions(env);
	sl_draw_collectibles(env);
	if (env->map[env->p1.pos.y][env->p1.pos.x] == MAP_ENNEMY)
		env->p1.alive = false;
	sl_render_bombs(env);
	if (env->p1.alive == true)
	{
		sl_render_p1(env);
		sl_render_ennemies(env);
		mlx_img = env->canvas.mlx_img;
		mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, mlx_img, 0, 0);
		sl_put_stage_name(env);
		sl_put_counts_to_window(env);
	}
	else
		sl_kill_p1(env);
	sl_put_message_at_start(env);
	return (0);
}
