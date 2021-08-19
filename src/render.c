/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 03:31:37 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/19 06:01:23 by dtanigaw         ###   ########.fr       */
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

void	sl_render_bloc_with_xpm(t_img *img, t_img *xpm_img, int x, int y)
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
				sl_img_pixel_put(img, j + x, i + y, color, true);
			++j;
		}
		++i;
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
				sl_render_buffer_with_colored_bloc(env->buffer_bkgd, 107830, BLOC_LEN * j, BLOC_LEN * i);
			else
				sl_render_buffer_bloc_with_xpm(env->buffer_bkgd, &env->tex.wall, BLOC_LEN * j, BLOC_LEN * i);
			if (map[i][j] == MAP_ITEM_BOMB)
				sl_render_buffer_bloc_with_xpm(env->buffer_bkgd, &env->tex.bomb.item_bomb, BLOC_LEN * j, BLOC_LEN * i);
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
	sl_render_bloc_with_xpm(&env->bkgd, curr_state, exit.pos.x * BLOC_LEN,  exit.pos.y * BLOC_LEN);
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
			sl_img_pixel_put(&env->bkgd, j, i, color, true);
			++j;
		}
		++i;
	}
}

void	sl_copy_bkgd_buffer_to_buffer(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->height * BLOC_LEN)
	{
		j = 0;
		while (j < env->width * BLOC_LEN)
		{
			env->buffer[i][j] = env->buffer_bkgd[i][j];
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

//put img to window (not render
int	sl_render(t_env *env)
{
	t_img	*img;
	t_img	*img2;
	static int	i;
	
	int	j;
	int			bomb_pos_x;
	int			bomb_pos_y;
	
//	sl_init_canvas(env);
//	sl_copy_bkgd_buffer_to_buffer(env);
//	env->buffer = env->buffer_bkgd;
	sl_put_buffer_bkgd_to_img(env);
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
	sl_render_bloc_with_xpm(&env->bkgd, img, env->p1.sub_pos.x, env->p1.sub_pos.y);

	j = 0;
	t_ennemies	ennemies;
	ennemies = env->tex.ennemies;
	while (j < ennemies.count) 
	{
		if (ennemies.sprites[j].alive == true)
		{
			img2 = env->tex.ennemies.sprites[j].curr_state;
			sl_render_bloc_with_xpm(&env->bkgd, img2, ennemies.sprites[j].sub_pos.x, ennemies.sprites[j].sub_pos.y);
		}
		++j;
	}

//	sl_put_buffer_to_img(env);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->bkgd.mlx_img, 0, 0);    

	sl_put_move_count_to_window(env);
	if (i <= CENTER_MESS_TIME)
	{
		sl_put_centered_message_to_window(env, "START !");
		++i;
	}
	return (0);
}
