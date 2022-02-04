/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:17:44 by lchan             #+#    #+#             */
/*   Updated: 2022/02/04 15:24:42 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUBBER_SIZE 0
# endif

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
	int				fd;
	char			*content;
	char			buff[BUFFER_SIZE + 1];
	struct s_list	*next;
}t_list;

//get_next_line_utils.c
size_t	ft_strlen_opt_newline(char *str, int opt_newline);
char	*ft_strjoinfree_content(t_list *nod);
void	gnl_free_block(t_list **head, t_list *nod);
t_list	*ft_struct_init(int fd);
t_list	*ft_lst_init_addback(t_list **head, int fd);

//get_next_line_bonus.c
void	ft_rebuild_buff(t_list *nod);
void	gnl_build_content(t_list **nod, int fd);
char	*get_next_line(int fd);

#endif
