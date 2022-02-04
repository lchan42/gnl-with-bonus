/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:15:01 by lchan             #+#    #+#             */
/*   Updated: 2022/02/04 15:15:06 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_opt_newline(char *str, int opt_newline)
{
	size_t	index;

	if (!str)
		return (0);
	index = 0;
	while (opt_newline == 1 && str[index])
	{
		if (str[index] == '\n')
			return (index + 1);
		index++;
	}
	if (opt_newline == 2)
	{
		while (str[index])
		{
			if (str[index] == '\n')
				return (1);
			index++;
		}
		return (0);
	}
	else if (opt_newline == 0)
		while (str[index])
			index++;
	return (index);
}
/**************************************************************
- opt_line = 1 : give the position after newline in the buffer. 
	Usefull for ft_strjoinfree and  buff_rebuild;
- opt_line = 2 : is equivalent to a strchr for new_line
- opt_newline = 0 : normal strlen; 
***************************************************************/

char	*ft_strjoinfree_content(t_list *nod)
{
	int		len_content;
	int		len_buff;
	int		index;
	char	*new_content;

	if (!nod->content && !nod->buff[0])
		return (NULL);
	len_content = ft_strlen_opt_newline(nod->content, 0);
	len_buff = ft_strlen_opt_newline(nod->buff, 1);
	index = -1;
	new_content = (char *)malloc((len_content + len_buff + 1) * sizeof (char));
	if (!new_content)
		return (NULL);
	while (++index < (int)len_content)
		*(new_content++) = nod->content[index];
	index = -1;
	while (++index < (int)len_buff)
		*(new_content++) = nod->buff[index];
	*(new_content) = '\0';
	if (nod->content)
		free(nod->content);
	return (new_content - (len_content + len_buff));
}

t_list	*ft_struct_init(int fd)
{	
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->fd = fd;
	tmp->content = NULL;
	while (++i < BUFFER_SIZE + 1)
		tmp->buff[i] = '\0';
	tmp->next = NULL;
	return (tmp);
}

t_list	*ft_lst_init_addback(t_list **head, int fd)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		i;

	i = -1;
	tmp = (*head);
	tmp2 = (*head);
	if (tmp)
		while (tmp->fd != fd)
			tmp = tmp->next;
	else
		tmp = ft_struct_init(fd);
	if (!*head)
		*head = tmp;
	else if (tmp2->next)
	{
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
	return (tmp);
}
