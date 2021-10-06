/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:45:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/05 17:21:25 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	sl_destroy_img(t_env *env, void **mlx_img)
{
	if (*mlx_img)
		mlx_destroy_image(env->mlx_ptr, *mlx_img);
}

void	sl_destroy_images(t_env *env)
{
	sl_destroy_img(env, &env->canvas.mlx_img);

	sl_destroy_img(env, &env->p1.img.up.one.mlx_img);
	sl_destroy_img(env, &env->p1.img.up.two.mlx_img);
	sl_destroy_img(env, &env->p1.img.up.three.mlx_img);
	sl_destroy_img(env, &env->p1.img.down.one.mlx_img);
	sl_destroy_img(env, &env->p1.img.down.two.mlx_img);
	sl_destroy_img(env, &env->p1.img.down.three.mlx_img);
	sl_destroy_img(env, &env->p1.img.left.one.mlx_img);
	sl_destroy_img(env, &env->p1.img.left.two.mlx_img);
	sl_destroy_img(env, &env->p1.img.left.three.mlx_img);
	sl_destroy_img(env, &env->p1.img.right.one.mlx_img);
	sl_destroy_img(env, &env->p1.img.right.two.mlx_img);
	sl_destroy_img(env, &env->p1.img.right.three.mlx_img);

	sl_destroy_img(env, &env->p1.img.dead.one.mlx_img);
	sl_destroy_img(env, &env->p1.img.dead.two.mlx_img);
	sl_destroy_img(env, &env->p1.img.dead.three.mlx_img);
	sl_destroy_img(env, &env->p1.img.dead.four.mlx_img);
	sl_destroy_img(env, &env->p1.img.dead.five.mlx_img);
	sl_destroy_img(env, &env->p1.img.dead.six.mlx_img);
	sl_destroy_img(env, &env->p1.img.dead.seven.mlx_img);
	sl_destroy_img(env, &env->p1.img.dead.eight.mlx_img);


	sl_destroy_img(env, &env->tex.ennemies.img.up.one.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.up.two.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.up.three.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.down.one.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.down.two.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.down.three.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.left.one.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.left.two.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.left.three.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.right.one.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.right.two.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.img.right.three.mlx_img);
	sl_destroy_img(env, &env->tex.ennemies.dead.mlx_img);
	
	sl_destroy_img(env, &env->tex.exit_pipe.state0.mlx_img);
	sl_destroy_img(env, &env->tex.exit_pipe.state1.mlx_img);
	sl_destroy_img(env, &env->tex.exit_pipe.state2.mlx_img);
	sl_destroy_img(env, &env->tex.exit_pipe.state3.mlx_img);
	sl_destroy_img(env, &env->tex.exit_pipe.state4.mlx_img);
	sl_destroy_img(env, &env->tex.exit_pipe.state5.mlx_img);

	sl_destroy_img(env, &env->tex.bomb.set_states.one.mlx_img);
	sl_destroy_img(env, &env->tex.bomb.set_states.two.mlx_img);
	sl_destroy_img(env, &env->tex.bomb.set_states.three.mlx_img);
	sl_destroy_img(env, &env->tex.bomb.explode_states.ctr.mlx_img);
	sl_destroy_img(env, &env->tex.bomb.explode_states.hrz.one.mlx_img);
	sl_destroy_img(env, &env->tex.bomb.explode_states.hrz.two.mlx_img);
	sl_destroy_img(env, &env->tex.bomb.explode_states.hrz.three.mlx_img);
	sl_destroy_img(env, &env->tex.bomb.explode_states.vrt.one.mlx_img);
	sl_destroy_img(env, &env->tex.bomb.explode_states.vrt.two.mlx_img);
	sl_destroy_img(env, &env->tex.bomb.explode_states.vrt.three.mlx_img);

	sl_destroy_img(env, &env->tex.bomb.item_bomb.mlx_img);
	sl_destroy_img(env, &env->tex.fire.img.mlx_img);
	sl_destroy_img(env, &env->tex.speed.img.mlx_img);
	sl_destroy_img(env, &env->tex.wall.mlx_img);
	sl_destroy_img(env, &env->tex.tile_shadow.mlx_img);
	sl_destroy_img(env, &env->icons.p1.mlx_img);
	sl_destroy_img(env, &env->icons.bomb.mlx_img);
}
