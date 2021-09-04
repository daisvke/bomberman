/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:51:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/04 13:36:56 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_free_array_of_pointers(char *map[], int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		ft_free(map[i]);
		++i;
	}
	ft_free(map);
}

char	**sl_get_array_of_error_messages(void)
{
	char	*array[30];

	array[0] = NULL;
	array[1] = "mlx init failed";
	array[2] = "failed to create new window";
	array[3] = "not enough arguments";
	array[4] = "map's file has no extension";
	array[5] = "map's file has the wrong extension (needs to be .ber)";
	array[6] = "memory allocation for the buffer failed";
	array[7] = "too many ennemies on the map";
	array[8] = "too many bomb items on the map";
	array[9] = "too many fire items on the map";
	array[10] = "too many speed items on the map";
	array[11] = "stage is not surrounded by walls";
	array[12] = "unknown element on the map";
	array[13] = "map has to contain at least one collectible";
	array[14] = "map has to contain one player";
	array[15] = "map has to contain an exit";
	array[16] = "map file failed to open";
	array[17] = "map is not a rectangle";
	array[18] = "function get_next_line failed";
	array[19] = "map is too small";
	return (array);
}

char	*sl_get_err_message_from_err_code(int err_code)
{
	char	**err_messages;
//	char	err_messages[30][60];

	err_messages = sl_get_array_of_error_messages();
	return (err_messages[err_code]);
}

int    sl_exit_game(t_env *env)
{
	if (env->map)
		sl_free_array_of_pointers(env->map, env->height);
	if (env->buffer_bkgd)
		sl_free_array_of_pointers(env->buffer_bkgd, env->height * BLOC_LEN);
	if (env->canvas.mlx_img) 
		mlx_destroy_image(env->mlx_ptr, env->canvas.mlx_img);
	if (env->win_ptr)
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	if (env->mlx_ptr)
	{
		mlx_loop_end(env->mlx_ptr);
		mlx_destroy_display(env->mlx_ptr);
		ft_free(env->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int    sl_set_err_code_and_exit_game(t_env *env, int err_code)
{
	char	*err_message;

	err_message = NULL;
	printf("Error code: %d", err_code);
	err_message = sl_get_err_message_from_err_code(err_code);
	printf("\033[31m\t\t%s\033[0m\n\n", err_message);
	sl_exit_game(env);
}

void	sl_exit_game_over(t_env *env)
{
	static int	i;
	int			collected;
	int			to_collect;

	collected = env->tex.bomb.collected - 1;
	to_collect = env->tex.bomb.to_collect;
	if (i <= CENTER_MESS_TIME)
		sl_put_centered_message_to_window(env, "GAME OVER !");
	else
	{
		printf("\n");
		printf("\033[31m\t\tGAME OVER !\033[0m\n\n");
		printf("Collected items: %d/%d\n", collected, to_collect);
		printf("\n");
		sl_exit_game(env);
	}
	++i;
}
