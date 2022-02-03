#include "get_next_line.h"

size_t	ft_strlen_opt_newline(char *str, int opt_newline)
{
	size_t	index;

	if (!str)
		return (0);
	index = 0;
	if (opt_newline == 1)
	{
		while (str[index])
		{
			if (str[index] == '\n')
				return (index + 1);
			index++;
		}
	}
	else if (opt_newline == 2)
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
/* 
3 in one funtion;
- opt_line = 1 : give the position after newline in the buffer. 
	Usefull for ft_strjoinfree and  buff_rebuild;
- opt_line = 2 : is equivalent to an strchr for new_line
- opt_newline = 0 : normal strlen; 
*/

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
		return NULL;
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
/*
len_buff is caculated with opt_newline = 1. it will give the position after the newline.
ft_strjoinfree_content free the malloced nod->content if it exite.
*/
/*
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
	nod->position = len_buff;
	index = -1;
	new_content = (char *)malloc((len_content + len_buff + 1) * sizeof (char));
	if (!new_content)
		return NULL;
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
 this version is stocking the position in strjoinfree
   position is used in rebuild_buff
   
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
*/
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
/*
	
**/

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
	if (!tmp)
	{
		tmp = malloc(sizeof(t_list));
		tmp->fd = fd;
		tmp->content = NULL;
		while (++i < BUFFER_SIZE + 1)
			tmp->buff[i] = '\0';
		tmp->position = 0;
		tmp->next = NULL;
	}
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


char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*nod;

	if (fd == -1)
		return (NULL);
	nod = ft_lst_init_addback(&head, fd);
	if (nod && nod->content)
	{
		//free (nod->content);
		nod->content = NULL;
	}
	gnl_build_content(&nod, nod->fd);
	if (!nod->content && !nod->buff[0]) //need to do free block for bonus
	{
		free(nod);
		nod = NULL;
	}
	if (nod)
		return (nod->content);
	else
		return (NULL);
}

//seems that does not work with empty files 
//freeing too much if file is empty

