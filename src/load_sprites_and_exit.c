/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites_and_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:40:29 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/09 18:42:42 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	sl_load_white_bomber(t_env *env)
{
	sl_load_texture(env, &env->p1.img.up.one, "./img/white-up-0.xpm");
	sl_load_texture(env, &env->p1.img.up.two, "./img/white-up-l.xpm");
	sl_load_texture(env, &env->p1.img.up.three, "./img/white-up-r.xpm");
	sl_load_texture(env, &env->p1.img.down.one, "./img/white-down-0.xpm");
	sl_load_texture(env, &env->p1.img.down.two, "./img/white-down-l.xpm");
	sl_load_texture(env, &env->p1.img.down.three, "./img/white-down-r.xpm");
	sl_load_texture(env, &env->p1.img.left.one, "./img/white-left-0.xpm");
	sl_load_texture(env, &env->p1.img.left.two, "./img/white-left-l.xpm");
	sl_load_texture(env, &env->p1.img.left.three, "./img/white-left-r.xpm");
	sl_load_texture(env, &env->p1.img.right.one, "./img/white-right-0.xpm");
	sl_load_texture(env, &env->p1.img.right.two, "./img/white-right-l.xpm");
	sl_load_texture(env, &env->p1.img.right.three, "./img/white-right-r.xpm");
	sl_load_texture(env, &env->p1.img.dead.one, "./img/white-dead-0.xpm");
	sl_load_texture(env, &env->p1.img.dead.two, "./img/white-dead-1.xpm");
	sl_load_texture(env, &env->p1.img.dead.three, "./img/white-dead-2.xpm");
	sl_load_texture(env, &env->p1.img.dead.four, "./img/white-dead-3.xpm");
	sl_load_texture(env, &env->p1.img.dead.five, "./img/white-dead-4.xpm");
	sl_load_texture(env, &env->p1.img.dead.six, "./img/white-dead-5.xpm");
	sl_load_texture(env, &env->p1.img.dead.seven, "./img/white-dead-6.xpm");
	sl_load_texture(env, &env->p1.img.dead.eight, "./img/white-dead-7.xpm");
}

void	sl_load_ennemies_vertical(t_env *env)
{
	t_img	*img;

	img = &env->tex.ennemies.img.up.one;
	sl_load_texture(env, img, "./img/ennemy-up-0.xpm");
	img = &env->tex.ennemies.img.up.two;
	sl_load_texture(env, img, "./img/ennemy-up-l.xpm");
	img = &env->tex.ennemies.img.up.three;
	sl_load_texture(env, img, "./img/ennemy-up-r.xpm");
	img = &env->tex.ennemies.img.down.one;
	sl_load_texture(env, img, "./img/ennemy-down-0.xpm");
	img =  &env->tex.ennemies.img.down.two;
	sl_load_texture(env, img, "./img/ennemy-down-l.xpm");
	img = &env->tex.ennemies.img.down.three;
	sl_load_texture(env, img, "./img/ennemy-down-r.xpm");
}

void	sl_load_ennemies_horizontal(t_env *env)
{
	t_img	*img;

	img = &env->tex.ennemies.img.left.one;
	sl_load_texture(env, img, "./img/ennemy-left-0.xpm");
	img = &env->tex.ennemies.img.left.two;
	sl_load_texture(env, img, "./img/ennemy-left-l.xpm");
	img = &env->tex.ennemies.img.left.three;
	sl_load_texture(env, img, "./img/ennemy-left-r.xpm");
	img = &env->tex.ennemies.img.right.one;
	sl_load_texture(env, img, "./img/ennemy-right-0.xpm");
	img = &env->tex.ennemies.img.right.two;
	sl_load_texture(env, img, "./img/ennemy-right-l.xpm");
	img = &env->tex.ennemies.img.right.three;
	sl_load_texture(env, img, "./img/ennemy-right-r.xpm");
}

void	sl_load_ennemies(t_env *env)
{
	t_img	*dead;

	sl_load_ennemies_vertical(env);
	sl_load_ennemies_horizontal(env);
	dead = &env->tex.ennemies.dead;
	sl_load_texture(env, dead, "./img/ennemy-dead.xpm");
}

void	sl_load_exit(t_env *env)
{
	sl_load_texture(env, &env->tex.exit_pipe.state0, "./img/exit-0.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state1, "./img/exit-1.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state2, "./img/exit-2.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state3, "./img/exit-3.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state4, "./img/exit-4.xpm");
	sl_load_texture(env, &env->tex.exit_pipe.state5, "./img/exit-5.xpm");
}
