/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:05:23 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/08/07 04:05:52 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	sl_handle_input(int keysym, t_env *env)
{
	if (keysym == XK_Escape)
	{
		mlx_loop_end(env->mlx_ptr);
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	}
	return (0);
}

/*
int	sl_handle_keypress(int keysym, t_env *env)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	return (0);
}
*/

int	sl_handle_keypress(int keycode, t_env *env)
{
	char		**map;
	int			x;
	int			y;
	t_dir		dir;

	map = env->map;
	x = env->p1.pos.x;
	y = env->p1.pos.y;
	if (keycode == XK_w)
		env->p1.curr_dir.up = true;
	if (keycode == XK_s)
		env->p1.curr_dir.down = true;
	if (keycode == XK_a)
		env->p1.curr_dir.left = true;
	if (keycode == XK_d)
		env->p1.curr_dir.right = true;
	dir = env->p1.curr_dir;
	return (0);
}

void	check_map(t_env *env)
{
	int i, j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%c", env->map[i][j]);
			++j;
		}
		printf("\n");
		++i;
	}
}

void	sl_init_env(t_env *env)
{
	/*
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		bkgd;
	int			width;
	int			height;
	char		**map;
	t_textures	tex;
	t_player	p1;
	*/
	env->tex.bomb.to_collect = 0;
	env->tex.bomb.collected = 0;
	env->tex.exit.appear = false;
	env->p1.moves = 0;
	env->p1.curr_dir.up = false;
	env->p1.curr_dir.down = false;
	env->p1.curr_dir.left = false;
	env->p1.curr_dir.right = false;
	env->p1.curr_state = &env->p1.img.down.def;
	env->p1.sub_pos.x = 0;
	env->p1.sub_pos.y = 0;
	env->p1.pos.x = 0;
	env->p1.pos.y = 0;
}

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

void	sl_load_all_textures(t_env *env)
{
	sl_load_texture(env, &env->tex.wall, "./img/grey-tile-24x24.xpm");
	sl_load_texture(env, &env->tex.bomb.item_bomb, "./img/item-bomb-24x24.xpm");
	sl_load_texture(env, &env->p1.img.up.def, "./img/white-up-0-24x24.xpm");
	sl_load_texture(env, &env->p1.img.up.l, "./img/white-up-l-24x24.xpm");
	sl_load_texture(env, &env->p1.img.up.r, "./img/white-up-r-24x24.xpm");
	sl_load_texture(env, &env->p1.img.down.def, "./img/white-down-0-24x24.xpm");
	sl_load_texture(env, &env->p1.img.down.l, "./img/white-down-l-24x24.xpm");
	sl_load_texture(env, &env->p1.img.down.r, "./img/white-down-r-24x24.xpm");
	sl_load_texture(env, &env->p1.img.left.def, "./img/white-left-0-24x24.xpm");
	sl_load_texture(env, &env->p1.img.left.l, "./img/white-left-l-24x24.xpm");
	sl_load_texture(env, &env->p1.img.left.r, "./img/white-left-r-24x24.xpm");
	sl_load_texture(env, &env->p1.img.right.def, "./img/white-right-0-24x24.xpm");
	sl_load_texture(env, &env->p1.img.right.l, "./img/white-right-l-24x24.xpm");
	sl_load_texture(env, &env->p1.img.right.r, "./img/white-right-r-24x24.xpm");
	sl_load_texture(env, &env->tex.exit.state0, "./img/exit-0-24x24.xpm");
	sl_load_texture(env, &env->tex.exit.state1, "./img/exit-1-24x24.xpm");
	sl_load_texture(env, &env->tex.exit.state2, "./img/exit-2-24x24.xpm");
	sl_load_texture(env, &env->tex.exit.state3, "./img/exit-3-24x24.xpm");
	sl_load_texture(env, &env->tex.exit.state4, "./img/exit-4-24x24.xpm");
	sl_load_texture(env, &env->tex.exit.state5, "./img/exit-5-24x24.xpm");
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned)s1[i] - (unsigned)s2[i]);
}

void	sl_check_input(int argc, char *filename)
{
	char	*file_extension;

	if (argc < 2)
		exit(EXIT_FAILURE);
	file_extension = ft_strrchr(filename, '.');
	if (!file_extension)
		exit(EXIT_FAILURE);
	if (ft_strcmp(file_extension, FILE_EXTENSION) != 0)
		exit(EXIT_FAILURE);
}

void    sl_exit_game(t_env *env, char *err_mess)
{
    free(env->map);
    if (err_mess)
        ft_printf("error; %s\n", err_mess);
	mlx_loop(env.mlx_ptr);
	mlx_destroy_display(env.mlx_ptr);
	ft_free(env.mlx_ptr);
    exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	int		width;
	int		height;

	sl_check_input(argc, argv[1]);
	sl_init_env(&env);
	sl_parse_map(&env, argv[1]);

	width = env.width * BLOC_LEN;
	height = env.height * BLOC_LEN;

	env.mlx_ptr = mlx_init();
	if (!env.mlx_ptr)
		exit(EXIT_FAILURE);
	env.win_ptr = mlx_new_window(env.mlx_ptr, width, height, \
		"BOMBERMAN");
	if (!env.win_ptr)
	{
		free(env.mlx_ptr);
		exit(EXIT_FAILURE);
	}
	sl_load_all_textures(&env);
	env.bkgd.mlx_img = mlx_new_image(env.mlx_ptr, width, height);
	env.bkgd.addr = mlx_get_data_addr(env.bkgd.mlx_img, &env.bkgd.bpp, &env.bkgd.line_len, &env.bkgd.endian);
	
	sl_render_bkgd(&env);

	mlx_hook(env.win_ptr, 2, 1L << 0, sl_handle_keypress, &env);
	mlx_key_hook(env.win_ptr, &sl_handle_input, &env);
	mlx_loop_hook(env.mlx_ptr, &sl_render, &env);
    sl_exit_game(&env, NULL);
	exit(EXIT_SUCCESS);
}
