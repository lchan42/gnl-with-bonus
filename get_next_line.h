/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:38:47 by lchan             #+#    #+#             */
/*   Updated: 2022/01/30 20:28:41 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
# ifndef MAX_OPEN
# define MAX_OPEN 1024
# endif
*/

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>


typedef struct s_list
{
	int		fd;
	char	*content;
	char	buff[BUFFER_SIZE + 1];
	size_t	position;
	struct	s_list	*next;
}t_list;

char	*get_next_line(int fd);
#endif
