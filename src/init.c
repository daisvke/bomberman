/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 14:16:58 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/15 14:29:21 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_init_buffer(t_env *env)
{
	int	i;
	int	height;
	int	width;

	height = env->height * BLOC_LEN;
	width= env->width * BLOC_LEN;
	env->buffer_bkgd = malloc(sizeof(int *) * height);
	if (!env->buffer_bkgd)
		sl_put_err_code_and_exit_game(env, 6);
	i = 0;
	while (i < height)
	{
		env->buffer_bkgd[i] = malloc(sizeof(int) * width);
		++i;
	}
}

void	sl_init_env(t_env *env, char *stage_name)
{
	t_bombs	*bomb;

	bomb = &env->tex.bomb;
	env->width = 0;
	env->height = 0;
	env->map = NULL;
	sl_init_errors(env);
	bomb->to_collect = 0;
	bomb->collected = 1;
	bomb->set_bombs_nbr = 0;	
	bomb->explode_size = 2;
	sl_init_set_bomb(&env->tex.bomb.set_bombs[0], false, 0, 0, 0);
	env->tex.fire.to_collect = 0;
	env->tex.speed.to_collect = 0;
	env->tex.ennemies.count = 0;
	sl_init_sprite(&env->p1, 0, 0, PLAYER_SPEED);
	env->stage_name = stage_name;
}

void	sl_init_canvas(t_env *env, int width, int height)
{
	void	**mlx_img;
	int		*bpp;
	int		*line_len;
	int		*endian;

	mlx_img = &env->canvas.mlx_img;
	bpp =  &env->canvas.bpp;
	line_len = &env->canvas.line_len;
	endian = &env->canvas.endian;
	env->canvas.mlx_img = mlx_new_image(env->mlx_ptr, width, height);
	env->canvas.addr = mlx_get_data_addr(*mlx_img, bpp, line_len, endian);
}

void	sl_init_all(t_env *env, char *argv[])
{
	int	width;
	int	height;

	sl_init_env(env, argv[1]);
	sl_parse_map(env, argv[1]);
	sl_check_errors_1(env);
	width = env->width * BLOC_LEN;
	height = env->height * BLOC_LEN;
	sl_init_buffer(env);
	sl_init_mlx(env, width, height);
	sl_load_all_textures(env);
	sl_init_canvas(env, width, height);
	sl_render_background(env);
	sl_put_buffer_bkgd_to_img(env);
}
