/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:45:06 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/06 23:49:50 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_destroy_img(t_env *env, void **mlx_img)
{
	if (*mlx_img)
		mlx_destroy_image(env->mlx_ptr, *mlx_img);
}

void	sl_destroy_all_images(t_env *env)
{
	sl_destroy_img(env, &env->canvas.mlx_img);
	sl_destroy_white_bomber(env);
	sl_destroy_ennemies(env);
	sl_destroy_exit(env);
	sl_destroy_bomb(env);
	sl_destroy_collectibles(env);
	sl_destroy_img(env, &env->tex.wall.mlx_img);
	sl_destroy_img(env, &env->tex.tile_shadow.mlx_img);
	sl_destroy_img(env, &env->icons.p1.mlx_img);
	sl_destroy_img(env, &env->icons.bomb.mlx_img);
}
