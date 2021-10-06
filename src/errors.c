/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:38:50 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/06 20:58:09 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_fill_array_with_err_1(char **array)
{
	array[0] = "failed to load texture";
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
}

void	sl_fill_array_with_err_2(char **array)
{
	array[12] = "unknown element on the map";
	array[13] = "map has to contain at least one collectible";
	array[14] = "map has to contain one player";
	array[15] = "map has to contain an exit";
	array[16] = "function get_next_line failed";
	array[17] = "map is too small";
	array[18] = "map is not a rectangle";
	array[19] = "failed to open file";
	array[20] = "failed to allocate memory";
	array[21] = "failed to close file";
}

char	**sl_get_array_of_error_messages(char *errors[])
{
	sl_fill_array_with_err_1(errors);
	sl_fill_array_with_err_2(errors);
	return (errors);
}

char	*sl_get_err_message_from_err_code(int err_code)
{
	char	*err_messages[ERR_MAX + 1];

	sl_get_array_of_error_messages(err_messages);
	return (err_messages[err_code]);
}

void	sl_print_err_message(int err_code)
{
	char	*err_message;

	err_message = NULL;
	sl_put_str_to_terminal("\nError code: ");
	sl_put_nbr_to_terminal(err_code);
	err_message = sl_get_err_message_from_err_code(err_code);
	sl_put_colored_str_to_terminal(err_message, STR_RED);
}
