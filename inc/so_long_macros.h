/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_macros.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 05:37:16 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/20 01:24:59 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_MACROS_H
# define SO_LONG_MACROS_H

/*
** string colors
*/
# define STR_WHITE			"\033[0m"
# define STR_RED			"\033[31m"
# define STR_CYAN			"\033[36m"

# define FILE_EXTENSION		".ber"
# define FILE_EXTENSION_LEN	3
# define SAME				0

# define ERR_MAX			22

# define BLOC_LEN			24
# define MAP_ELEMS			"01CEPM"
# define MAP_COLLECTIBLES	"BFS"

# define ENNEMY_LIMIT		20
# define ITEM_LIMIT			50

# define MAP_FLOOR			'0'
# define MAP_WALL			'1'
# define MAP_ITEM_BOMB		'B'
# define MAP_FIRE			'F'
# define MAP_SPEED			'S'
# define MAP_EXIT			'3'
# define MAP_PLAYER			'4'
# define MAP_ENNEMY			'5'

# define UP					-1
# define DOWN				1
# define LEFT				-1
# define RIGHT				1

/*
** current direction
*/
# define CR_UP				8
# define CR_DOWN			4
# define CR_LEFT			2
# define CR_RIGHT			1

# define NO_AVAILABLE_SLOT	-1

/*
** parsing
*/
# define SUCCESS			0
# define ERROR				-1
# define COLLECTIBLE		2
# define EXIT				3
# define PLAYER				4
# define ENNEMY             5

/*
** colors
*/
# define WHITE				0xFFFFFF
# define GREEN				0x107830

/*
**	write to window 
*/
# define CENTER_MESS_TIME	1000

/*
** speeds
*/
# define PLAYER_SPEED		250
# define ENNEMY_SPEED		500
# define BOMB_SET_TIME		4280
# define BOMB_EXPLODE_TIME	1000
# define REVEAL_EXIT_SPEED	400

/*
** determine ennemy position
*/
# define UP_LEN				0
# define DOWN_LEN			1
# define LEFT_LEN			2
# define RIGHT_LEN			3
# define KEEP				1
# define FOUND_PLAYER		1

/*
** bombs
*/
# define START_BOMB			1

/*
** death
*/
# define PLAYER_DEATH_TIME	1000
# define ENNEMY_DEATH_TIME	1100

#endif
