/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:38:50 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/09/15 16:45:42 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	sl_fill_array_with_err_1(char **array)
{
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
}

void	sl_fill_array_with_err_2(char **array)
{
	array[12] = "unknown element on the map";
	array[13] = "map has to contain at least one collectible";
	array[14] = "map has to contain one player";
	array[15] = "map has to contain an exit";
	array[16] = "map file failed to open";
	array[17] = "map is not a rectangle";
	array[18] = "function get_next_line failed";
	array[19] = "map is too small";
	array[20] = "failed to allocate memory";
	array[21] = "failed to open file";
	array[22] = "failed to close file";
	array[23] = "failed to load texture";
}

char	**sl_get_array_of_error_messages(void)
{
	char	*array[30];

	sl_fill_array_with_err_1(array);
	sl_fill_array_with_err_2(array);
	return (array);
}

char	*sl_get_err_message_from_err_code(int err_code)
{
	char	**err_messages;

	err_messages = sl_get_array_of_error_messages();
	return (err_messages[err_code]);
}
