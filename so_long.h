/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:19:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/07/29 14:16:53 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <X11/X.h>

/*
** screen
*/
# define WINDOW_WIDTH		400
# define WINDOW_HEIGHT		200

# define BLOC_PXL_LEN		24
# define MAP_ELEMS			"01CEP"

/*
** colors
*/
# define GREEN_PIXEL		0x107830

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
}			t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_img	player;
	int		width;
	int		height;
	char	**map;
}			t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}		t_rect;

/*
** parse
*/
void	sl_parse_map(t_data *data, char *filename);

/*
** render
*/
void	sl_img_pixel_put(t_img *img, int x, int y, int color);
int		sl_render(t_data *data);
void	sl_render_background(t_img *img, int color);
void	sl_render_bloc_with_xpm(t_data *data, t_img *img, int x, int y);
int		sl_render_colored_bloc(t_img *img, int color, int x, int y);

#endif
