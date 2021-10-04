/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:40:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/03 20:49:39 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	sl_load_texture(t_env *env, t_img *img, char *path_to_file)
{
	void	**mlx;
	char	**addr;
	int		w;
	int		h;

	mlx = &img->mlx_img;
	*mlx = mlx_xpm_file_to_image(env->mlx_ptr, path_to_file, &w, &h);
	if (!img->mlx_img)
		sl_put_err_code_and_exit_game(env, 0);
	addr = &img->addr;
	*addr = mlx_get_data_addr(*mlx, &img->bpp, &img->line_len, &img->endian);
}

void	sl_load_set_bomb(t_env *env)
{
	t_img	*state_1;
	t_img	*state_2;
	t_img	*state_3;

	state_1 = &env->tex.bomb.set_states.one;
	sl_load_texture(env, state_1, "./img/set-bomb-0.xpm");
	state_2 = &env->tex.bomb.set_states.two;
	sl_load_texture(env, state_2, "./img/set-bomb-1.xpm");
	state_3 = &env->tex.bomb.set_states.three;
	sl_load_texture(env, state_3, "./img/set-bomb-2.xpm");
}

void	sl_load_bomb_explode(t_env *env)
{
	t_img	*img;

	img = &env->tex.bomb.explode_states.ctr;
	sl_load_texture(env, img, "./img/bomb-explode-ctr.xpm");
	img = &env->tex.bomb.explode_states.hrz.one;
	sl_load_texture(env, img, "./img/bomb-explode-hrz.xpm");
	img = &env->tex.bomb.explode_states.hrz.two;
	sl_load_texture(env, img, "./img/bomb-explode-hrz-l.xpm");
	img = &env->tex.bomb.explode_states.hrz.three;
	sl_load_texture(env, img, "./img/bomb-explode-hrz-r.xpm");
	img = &env->tex.bomb.explode_states.vrt.one;
	sl_load_texture(env, img, "./img/bomb-explode-vrt.xpm");
	img = &env->tex.bomb.explode_states.vrt.two;
	sl_load_texture(env, img, "./img/bomb-explode-vrt-u.xpm");
	img = &env->tex.bomb.explode_states.vrt.three;
	sl_load_texture(env, img, "./img/bomb-explode-vrt-d.xpm");
}

void	sl_load_items(t_env *env)
{
	sl_load_texture(env, &env->tex.bomb.item_bomb, "./img/item-bomb.xpm");
	sl_load_texture(env, &env->tex.fire.img, "./img/item-fire.xpm");
	sl_load_texture(env, &env->tex.speed.img, "./img/item-speed.xpm");
}

void	sl_load_all_textures(t_env *env)
{
	t_img	*tile;

	sl_load_texture(env, &env->tex.wall, "./img/grey-tile.xpm");
	sl_load_items(env);
	tile = &env->tex.tile_shadow;
	sl_load_texture(env, tile, "./img/green-tile-with-shadow.xpm");
	sl_load_set_bomb(env);
	sl_load_bomb_explode(env);
	sl_load_white_bomber(env);
	sl_load_texture(env, &env->p1.icon, "./img/display-white-icon.xpm");
	sl_load_texture(env, &env->icon_bomb, "./img/display-bomb.xpm");
	sl_load_ennemies(env);
	sl_load_exit(env);
}
