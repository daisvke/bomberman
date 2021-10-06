/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 04:07:38 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/06 19:30:35 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** Default size of the buffer used while reading from the fd
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 	32
# endif

# define NOT_FOUND		0
# define OFF			-1

/*
** return values
*/
# define ERROR 			-1
# define REACHED_EOF 	0
# define LINE_READ		1

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);

#endif
