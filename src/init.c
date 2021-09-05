/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 14:16:58 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/05 05:46:15 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_init_buffer(t_env *env)
{
	int	i;

	i = 0;
	env->buffer_bkgd = malloc(sizeof(int *) * env->height * BLOC_LEN);
	if (!env->buffer_bkgd)
		sl_set_err_code_and_exit_game(env, 6);
	i = 0;
	while (i < env->height * BLOC_LEN)
	{
		env->buffer_bkgd[i] = malloc(sizeof(int) * env->width * BLOC_LEN);
		++i;
	}
}

void	sl_init_set_bomb(t_items *bomb, bool draw, int x, int y, int size)
{
	bomb->draw = draw;
	bomb->pos.x = x;
	bomb->pos.y = y;
	bomb->explode_size = size;
	bomb->time1 = 0;
	bomb->time2 = 0;
	bomb->time3 = 0;
}

void	sl_init_sprite(t_sprite *sprite, int x, int y, int speed)
{
	sprite->alive = true;
	sprite->time_death = 0;
	sprite->moves = 0;
	sprite->curr_dir.up = false;
	sprite->curr_dir.down = false;
	sprite->curr_dir.left = false;
	sprite->curr_dir.right = false;
	sprite->curr_state = &sprite->img.down.one;
	sprite->sub_pos.x = 0;
	sprite->sub_pos.y = 0;
	sprite->pos.x = x;
	sprite->pos.y = y;
	sprite->speed = speed;
	sprite->time = 0;
}

void	sl_init_errors(t_env *env)
{
	int	i;

	i = 0;
	while (i < ERR_MAX)
	{
		env->errors[i] = false;
		++i;
	}
}

void	sl_init_env(t_env *env)
{
	env->width = 0;
	env->height = 0;
	env->map = NULL;
	sl_init_errors(env);
	env->tex.bomb.to_collect = 0;
	env->tex.bomb.collected = 1;
	env->tex.bomb.explode_size = 2;
	sl_init_set_bomb(&env->tex.bomb.set_bombs[0], false, 0, 0, 0);
	env->tex.fire.to_collect = 0;
	env->tex.speed.to_collect = 0;
	env->tex.ennemies.count = 0;
	sl_init_sprite(&env->p1, 0, 0, PLAYER_SPEED);
}

void	sl_check_errors(t_env *env)
{
	int		i;
	bool	quit;

	quit = false;
	i = 0;
	while (i < ERR_MAX)
	{
		if (env->errors[i] == true)
		{
			sl_print_err_message(env, i);
			quit = true;
		}
		++i;
	}
	if (quit == true)
		sl_exit_game(env);
}

void	sl_init_all(t_env *env, char *argv[])
{
	int		width;
	int		height;

	sl_init_env(env);
	sl_parse_map(env, argv[1]);
	sl_check_errors(env);
	width = env->width * BLOC_LEN;
	height = env->height * BLOC_LEN;
	sl_init_buffer(env);
	sl_init_mlx(env, width, height);
	sl_load_all_textures(env);
	env->canvas.mlx_img = mlx_new_image(env->mlx_ptr, width, height);
	env->canvas.addr = mlx_get_data_addr(env->canvas.mlx_img, &env->canvas.bpp, &env->canvas.line_len, &env->canvas.endian);
	sl_render_background(env);
	sl_put_buffer_bkgd_to_img(env);
}
