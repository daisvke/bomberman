/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:40:34 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/17 22:00:27 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_load_texture(t_env *env, t_img *img, char *path_to_file)
{
	int	width;
	int	height;

	img->mlx_img = mlx_xpm_file_to_image(env->mlx_ptr, path_to_file, &width, &height);
	if (!img->mlx_img)
	{
		printf("texture loading error\n");
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
}

void	sl_load_set_bomb(t_env *env)
{
	sl_load_texture(env, &env->tex.bomb.set_states.one, "./img/set-bomb-0-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.set_states.two, "./img/set-bomb-1-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.set_states.three, "./img/set-bomb-2-24x24.xpm");
}

void	sl_load_bomb_explode(t_env *env)
{
	sl_load_texture(env, &env->tex.bomb.explode_states.ctr, "./img/bomb-explode-ctr-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.explode_states.hrz.one, "./img/bomb-explode-hrz-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.explode_states.hrz.two, "./img/bomb-explode-hrz-l-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.explode_states.hrz.three, "./img/bomb-explode-hrz-r-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.explode_states.vrt.one, "./img/bomb-explode-vrt-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.explode_states.vrt.two, "./img/bomb-explode-vrt-u-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.explode_states.vrt.three, "./img/bomb-explode-vrt-d-24x24.xpm");
}

void	sl_load_p1(t_env *env)
{
	sl_load_texture(env, &env->p1.img.up.one, "./img/white-up-0-24x24.xpm");
	sl_load_texture(env, &env->p1.img.up.two, "./img/white-up-l-24x24.xpm");
	sl_load_texture(env, &env->p1.img.up.three, "./img/white-up-r-24x24.xpm");
	sl_load_texture(env, &env->p1.img.down.one, "./img/white-down-0-24x24.xpm");
	sl_load_texture(env, &env->p1.img.down.two, "./img/white-down-l-24x24.xpm");
	sl_load_texture(env, &env->p1.img.down.three, "./img/white-down-r-24x24.xpm");
	sl_load_texture(env, &env->p1.img.left.one, "./img/white-left-0-24x24.xpm");
	sl_load_texture(env, &env->p1.img.left.two, "./img/white-left-l-24x24.xpm");
	sl_load_texture(env, &env->p1.img.left.three, "./img/white-left-r-24x24.xpm");
	sl_load_texture(env, &env->p1.img.right.one, "./img/white-right-0-24x24.xpm");
	sl_load_texture(env, &env->p1.img.right.two, "./img/white-right-l-24x24.xpm");
	sl_load_texture(env, &env->p1.img.right.three, "./img/white-right-r-24x24.xpm");
}

void	sl_load_ennemies(t_env *env)
{
	sl_load_texture(env, &env->tex.ennemies.img.up.one, "./img/ennemy-up-0-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.up.two, "./img/ennemy-up-l-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.up.three, "./img/ennemy-up-r-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.down.one, "./img/ennemy-down-0-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.down.two, "./img/ennemy-down-l-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.down.three, "./img/ennemy-down-r-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.left.one, "./img/ennemy-left-0-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.left.two, "./img/ennemy-left-l-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.left.three, "./img/ennemy-left-r-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.right.one, "./img/ennemy-right-0-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.right.two, "./img/ennemy-right-l-24x24.xpm");
	sl_load_texture(env, &env->tex.ennemies.img.right.three, "./img/ennemy-right-r-24x24.xpm");
}

void	sl_load_exit(t_env *env)
{
	sl_load_texture(env, &env->tex.exit_pipe.state0, "./img/exit-0-24x24.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state1, "./img/exit-1-24x24.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state2, "./img/exit-2-24x24.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state3, "./img/exit-3-24x24.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state4, "./img/exit-4-24x24.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state5, "./img/exit-5-24x24.xpm");
}

void	sl_load_all_textures(t_env *env)
{
	sl_load_texture(env, &env->tex.wall, "./img/grey-tile-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.item_bomb, "./img/item-bomb-24x24.xpm");
	sl_load_set_bomb(env);
	sl_load_bomb_explode(env);
	sl_load_p1(env);
	sl_load_ennemies(env);
	sl_load_exit(env);
}
