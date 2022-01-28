/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:58:12 by lchan             #+#    #+#             */
/*   Updated: 2022/01/26 20:17:47 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str, t_list *c_lst, int on_switch)
{
	size_t	index;
	size_t	start;

	if (!str)
		return (0);
	index = 0;
	start = 0;
	if (on_switch)
	{
		start = c_lst-> buff_position;
///		printf("start = %zu\n", start);
		c_lst->buff_position = 0;
	}
	while (str[index + start])
	{
		if (str[index + start] == '\n')
		{
//			printf("returning index = %zu", index + 1);
			if (on_switch)
				c_lst->buff_position = index + start + 1;
			else
				return (0);
			return (index + 1);
		}
		index++;
	}
	return (index);
}


char	*ft_strjoinfree_s1(const char *s1, const char *s2, t_list *c_lst, size_t buff_position)
{
	size_t		len_s1;
	size_t		len_s2;
	int		index;
	char	*joined_str;

	if (!s1 && !s2)
		return (NULL);
	
	len_s1 = ft_strlen_gnl(s1, c_lst, 0);
	len_s2 = ft_strlen_gnl(s2, c_lst, 1);
//	printf("buff_position = %zu vs c_lst->buff_position = %zu\n", buff_position, c_lst->buff_position);
//	printf("len_s1 = %zu, len_s2 = %zu\n",len_s1,  len_s2);
	index = -1;
	joined_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	while (++index < len_s1)
		*(joined_str++) = s1[index];
	index = -1;
	while (++index < len_s2)
	{
//		printf("adding : s2[%zu] = [%c]\n", buff_position,  s2[buff_position]);
		*(joined_str++) = s2[buff_position++];
	}
	*(joined_str) = '\0';
	free((char *)s1);
	return (joined_str - (len_s1 + len_s2));
}

/***********************printf info function to delete *******************/
void	del_print_lst_content_and_address(t_list *lst)
{
	printf("fd = %d\n", lst->fd);
	printf("content = %s\n", lst->content);
}

void	ft_print_list_result(t_list *alst)
{

	int	i;

	i = 0;
	printf("\nthis is the current list whole content:\n");
	while (alst)
	{
		printf("t_list nbr %d \n->fd = %d\n", i++, alst->fd);
		printf("->content = %s\n", alst->content);
		printf("->buffer = %s\n", alst->buff);
		alst = alst->next;
	}
}

void	ft_print_current_lst(t_list *c_lst)
{
	int	i;

	i = 0;
	printf("\nthis is the current list content:\n");
	printf("t_list nbr %d \n->fd = %d\n", i++, c_lst->fd);
	printf("->content = %s\n", c_lst->content);
	printf("->buff_position = %zu\n", c_lst->buff_position);
	printf("->buffer = %s\n", c_lst->buff);	
}

/*************************** chain list fuction*****************************/

t_list  *ft_lstlast(t_list *lst)
{
        if (!lst)
                return (NULL);
        while (lst->next)
                lst = lst->next;
        return (lst);
}

t_list  *ft_lstnew(int fd)
{
        t_list  *tmp;
		int i;

		i = -1;
        tmp = malloc(sizeof(t_list));
        if (!tmp)
                return (NULL);
        tmp->fd = fd;
		tmp->content = NULL;
		while (++i < BUFFER_SIZE + 1 + sizeof(size_t))
			tmp->buff[i] = '\0';
		tmp->buff_position = 0;
        tmp->next = NULL;
        return (tmp);
}

void    ft_lstadd_back(t_list **alst, t_list *new)
{
        if (alst)
        {
                if (*alst == NULL)
                        *alst = new;
                else
                        ft_lstlast(*alst)->next = new;
        }
}

t_list	*ft_lstchr_feat_lstnew(t_list *lst, int fd)
{
	t_list	*tmp;

	if (lst->fd == 0 || !lst)
	{
		lst->fd = fd;
		return (lst);
	}
	else
	{
		tmp = lst;
		while (tmp)
		{
			if (tmp->fd == fd)
				return (tmp);
			tmp = tmp->next;
		}
		if (!tmp)
			ft_lstadd_back(&lst, ft_lstnew(fd));
	}
	return (ft_lstlast(lst));
}

void    free_list(t_list *alst)
{
        t_list  *tmp;

        tmp = alst;
        while (tmp)
        {
                free(tmp->content);
                tmp = tmp->next;
                free(alst);
                alst = tmp;
        }
}

void	build_content(t_list *c_lst)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	if (c_lst->content)
	{
		free(c_lst->content);
		c_lst->content = NULL;
		if (c_lst->buff_position == BUFFER_SIZE)
		{
			ret = read (c_lst->fd, c_lst->buff, BUFFER_SIZE);
			c_lst->buff_position = 0;
		}
	}
	while (1)
	{
//		printf("round %d content = %s\n", i, c_lst->content);
//		printf("round %d buff = %s\n", i, c_lst->buff);
//		printf("round %d buff_position = %zu\n\n", i++, c_lst->buff_position);
		if (c_lst->buff[0] != '\0')
			c_lst->content = ft_strjoinfree_s1(c_lst->content, c_lst->buff, c_lst, c_lst->buff_position);
//		printf("still in the loopc_lst->content = %s\n", c_lst->content);
		if (c_lst->content && !ft_strlen_gnl(c_lst->content, c_lst, 0))
		{
//			printf("I broke though here !!!!!!!!!!!\n");
			break ;
		}

		ret = read (c_lst->fd, c_lst->buff, BUFFER_SIZE);
		if (ret == BUFFER_SIZE)
			c_lst->buff[BUFFER_SIZE] = '\0';
		else
			c_lst->buff[ret] = '\0';
		if (!ret)
			break ;
	}
}

/*********************************gnl******************************/
char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	lst;
	t_list			*c_lst;
//	static tab[MAX_OPEN];

	next_line = NULL;
	c_lst = ft_lstchr_feat_lstnew(&lst, fd);
//	printf("working on fd nbr %d\n", c_lst->fd);
//	ft_print_list_result(&lst);
//	ft_print_current_lst(c_lst);
	build_content(c_lst);
	return (c_lst->content);
}
