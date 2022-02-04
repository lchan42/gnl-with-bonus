/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:13:55 by lchan             #+#    #+#             */
/*   Updated: 2022/02/04 15:14:02 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_rebuild_buff(t_list *nod)
{
	int	start;
	int	index;

	index = 0;
	start = ft_strlen_opt_newline(nod->buff, 1);
	while (nod->buff[start])
		nod->buff[index++] = nod->buff[start++];
	nod->buff[index] = '\0';
}

void	gnl_build_content(t_list **nod, int fd)
{
	int	ret;

	ret = -2;
	while (1)
	{
		if (!(*nod)->buff[0])
		{
			ret = read(fd, (*nod)->buff, BUFFER_SIZE);
			(*nod)->buff[ret] = '\0';
		}
		else
		{
			(*nod)->content = ft_strjoinfree_content(*nod);
			ft_rebuild_buff(*nod);
		}
		if (ft_strlen_opt_newline((*nod)->content, 2))
			break ;
		if (ret == 0 || ret == -1)
			break ;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*nod;

	if (fd <= -1 || BUFFER_SIZE <= 0)
		return (NULL);
	nod = ft_lst_init_addback(&head, fd);
	if (nod && nod->content)
		nod->content = NULL;
	gnl_build_content(&nod, nod->fd);
	if (!nod->content && !nod->buff[0])
	{
		gnl_free_block(&head, nod);
		if (nod == head)
			head = NULL;
		nod = NULL;
	}
	if (nod)
		return (nod->content);
	else
		return (NULL);
}
