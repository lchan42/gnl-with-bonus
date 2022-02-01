/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:58:12 by lchan             #+#    #+#             */
/*   Updated: 2022/02/01 16:57:16 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
// ok for removal
t_list  *ft_lstnew(int fd)
{
        t_list  *tmp;
		int i;
		int	ret;

		i = -1;
        tmp = malloc(sizeof(t_list));
        if (!tmp)
                return (NULL);
//		if (read (fd, tmp->buff, BUFFER_SIZE) <= 0) //if there is nothing to read or read is not possible free tmp and return null)
//		{
//			free(tmp);
//			return NULL;(should result in add null to the back);
//		}
        tmp->fd = fd;
		tmp->content = NULL;
		while (++i < BUFFER_SIZE + 1 + sizeof(size_t))//gonna have to remove this line if I decide to read above 
			tmp->buff[i] = '\0';// gonna have to remove this list coz i m reading above already
		tmp->position = 0;
        tmp->next = NULL;
        return (tmp);
}

t_list  *ft_lstlast(t_list *lst)
{
        if (!lst)
                return (NULL);
        while (lst->next)
                lst = lst->next;
        return (lst);
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
// of for removal
*/

/*size_t	ft_strlen_gnl(const char *str, t_list *c_lst, int on_switch)
{
	size_t	index;
	size_t	start;

	if (!str)
		return (0);
	index = 0;
	start = 0;
	if (on_switch)
	{
		start = c_lst->position;
		c_lst->position = 0;
	}
	while (str[index + start])
	{
		if (str[index + start] == '\n')
		{
//			printf("returning index = %zu", index + 1);
			if (on_switch)
				c_lst->position = index + start + 1;
			else
				return (0);
			return (index + 1);
		}
		index++;
	}
	return (index);
}

char	*ft_strjoinfree_s1(const char *s1, const char *s2, t_list *c_lst, size_t position)
{
	size_t		len_s1;
	size_t		len_s2;
	int			index;
	char		*joined_str;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen_gnl(s1, c_lst, 0);
	len_s2 = ft_strlen_gnl(s2, c_lst, 1);
//	printf("position = %zu vs c_lst->position = %zu\n", position, c_lst->position);
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
//		printf("adding : s2[%zu] = [%c]\n", position,  s2[position]);
		*(joined_str++) = s2[position++];
	}
	*(joined_str) = '\0';
	free((char *)s1);
	return (joined_str - (len_s1 + len_s2));
}


char	*ft_strjoinfree_s1(const char *s1, const char *s2, t_list *c_lst, size_t position)	// here position is not a pointer
{																							//cant remove s1 and s2 and use t_list
	size_t		len_s1;
	size_t		len_s2;
	int			index;
	char		*joined_str;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen_gnl(s1, c_lst, 0);
	len_s2 = ft_strlen_gnl(s2, c_lst, 1);//this function change the c_lst->positon if there is a \n
	index = -1;
	joined_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	while (++index < len_s1)
		*(joined_str++) = s1[index];
	index = -1;
	while (++index < len_s2)
		*(joined_str++) = s2[position++];
	*(joined_str) = '\0';
	if (s1)
		free((char *)s1);
	return (joined_str - (len_s1 + len_s2));
}

char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	*lst;
	t_list			*c_lst;

	next_line = NULL;
	c_lst = ft_lstchr_feat_lstnew(lst, fd);//find correct fd in the list
	if (c_lst && c_lst->content)
	{
		free(c_lst->content);
		c_lst->content = NULL;
		if (c_lst->position == BUFFER_SIZE)
		{
			if (!read(c_lst->fd, c_lst->buff, BUFFER_SIZE)) // read again coz position is at buffer size;
				c_lst->buff[0] = '\0';// need to free_block instead;
			c_lst->position = 0;//reset position coz position is at buffer size. 
		}
	}
//	printf("working on fd nbr %d\n", c_lst->fd);
//	ft_print_list_result(&lst);
//	ft_print_current_lst(c_lst);
	build_content(c_lst);
	return (c_lst->content);
}

t_list	*ft_lstchr_feat_addback(t_list *lst, int fd)
{
	if (lst)
	{
		while (lst->next && lst->fd != fd)
			lst = lst->next;
		if (lst->fd == fd)
			return (lst);
		lst->next = malloc(sizeof(t_list));
		if (!lst->next)
			return (NULL);
		lst = lst->next;
	}
	else
		lst = malloc(sizeof(t_list)); //i ve forgot to protect this malloc
	if (!read(fd, lst->buff, BUFFER_SIZE)) //case nothing to read (already read of unvalid fd)
	{
		free(lst);
		return (NULL);
	}
	lst->fd = fd;
	lst->content = NULL;
	lst->position = 0;
	lst->next = NULL;
	return (lst);
}

t_list	*ft_lstchr_feat_addback(t_list *lst, int fd)
{
	if (!lst)
		lst = malloc(sizeof(t_list));
	else 
	{
		while (lst->next && lst->fd != fd)
			lst = lst->next;
		if (lst->fd == fd)
			return (lst);
		lst->next = malloc(sizeof(t_list));
		lst = lst->next;//if malloc succes, lst = lst->next, if not lst = NULL
	}
	if (!lst)
		return (NULL);
	lst->fd = read(fd, lst->buff, BUFFER_SIZE); //save the return of read inside fd
	if (lst->fd > 0) //case nothing to read (already read of unvalid fd)
	{
		lst->content = NULL;
		lst->buff[lst->fd] = '\0';
		lst->fd = fd;
		lst->position = 0;
		lst->next = NULL;
		return (lst);
	}
	free(lst);
	return (NULL);
}

t_list	*ft_lstchr_feat_addback(t_list **lst, int fd)
{
		
	printf("adresse if lst in addback fonction : [%p]\n", lst);
	if (*lst)
	{	
		write(1, "HERRRRRRRRE!\n", 13);
		while ((*lst)->next && (*lst)->fd != fd)
			(*lst) = (*lst)->next;
		if ((*lst)->fd == fd)
		{
			printf("returning fd = %d", (*lst)->fd);
			return ((*lst));
		}
		(*lst)->next = malloc(sizeof(t_list));
		(*lst) = (*lst)->next;//if malloc failed, lst = NULL
	}
	else
	{
		(*lst) = malloc(sizeof(t_list));
		printf("creating lst\n");
	}
	if (!(*lst))
		return (NULL);
	(*lst)->fd = read(fd, (*lst)->buff, BUFFER_SIZE); //save the return of read inside fd, case sending multiple time same fd
	if ((*lst)->fd > 0) //case nothing to read (already read of unvalid fd)
	{
		(*lst)->content = NULL;
		(*lst)->buff[(*lst)->fd] = '\0';
		(*lst)->fd = fd;
		(*lst)->position = 0;
		(*lst)->next = NULL;
		return (*lst);
	}
	printf("freee lst\n");
	free((*lst));
	return (NULL);
}

void    free_list(t_list *lst, int fd, int option_block) //add on off switch = a block or the whole liste;
{
	t_list  *tmp;

	if (option_block)
	{
		while (lst->fd != fd)
		{
			tmp = lst;
			lst = lst->next;
		}
		tmp->next = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		return ;
	}
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}
*/
/*
size_t	ft_strlen_gnl(const char *str, t_list *c_lst, int on_switch)//switch on = case buff, save position and return char to print
{
	size_t	start;
	size_t	index;

	if (!str)
		return (0);//protection
	start = 0;
	if (on_switch)
	{
		start = c_lst->position;
		c_lst->position = 0;
	}
	index = start;
	while (str[index])
	{
		if (str[index] == '\n')
		{
			if (on_switch)
				c_lst->position = index + 1; //on_switch : there is a \n in buff. save following position
			else
				return (0); // case there is a \n in the content.
			return (index - start + 1); // on_switch : return number of char to copie into malloc
		}
		index++;
	}
	return (index - start); // case no \n. return the correct value.
}

char	*ft_strjoinfree_s1(t_list *c_lst, size_t position)	// here position is not a pointer
{																							//cant remove s1 and s2 and use t_list
	size_t		len_s1;
	size_t		len_s2;
	int			index;
	char		*joined_str;

	if (!c_lst->content && !c_lst->buff[0])
		return (NULL);
	len_s1 = ft_strlen_gnl(c_lst->content, c_lst, 0);
	len_s2 = ft_strlen_gnl(c_lst->buff, c_lst, 1);//this function change the c_lst->positon if there is a \n
	index = -1;
	joined_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	while (++index < len_s1)
		*(joined_str++) = c_lst->content[index];
	index = -1;
	while (++index < len_s2)
		*(joined_str++) = c_lst->buff[position++];
	*(joined_str) = '\0';
	if (c_lst->content)
		free(c_lst->content);
	return (joined_str - (len_s1 + len_s2));
}

char	*ft_strjoinfree_s1(t_list *c_lst, size_t position)	// here position is not a pointer
{
	size_t		len_s1;
	size_t		len_s2;
	int			index;
	char		*joined_str;

	if (!c_lst->content && !c_lst->buff[0])
		return (NULL);
	len_s1 = ft_strlen_gnl(c_lst->content, c_lst, 0);
	len_s2 = ft_strlen_gnl(c_lst->buff, c_lst, 1);//this function change the c_lst->positon if there is a \n
	index = -1;
	joined_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	while (++index < len_s1)
		*(joined_str++) = c_lst->content[index];
	index = -1;
	while (++index < len_s2)
	{
		*(joined_str++) = c_lst->buff[position];
		c_lst->buff[position++] = '\0';
	}
	*(joined_str) = '\0';
	if (c_lst->content)
		free(c_lst->content);
	return (joined_str - (len_s1 + len_s2));
}

void free_block(t_list *lst, int fd) //because I use a static t_list, my first mod is not malloced. so I dont need to free it
{
	t_list	*tmp_head;
	t_list	*tmp_tail;

	if (!lst)
		return ;
	tmp_head = lst;
	if (tmp_head->next)
		tmp_tail = tmp_head->next;
	while (tmp_tail->fd != fd)
	{
		tmp_head = tmp_head->next;
		tmp_tail = tmp_tail->next;
	}
	tmp_head->next = tmp_tail->next;
	if (tmp_tail->content)
	{
		free(tmp_tail->content);
		tmp_tail->content = NULL;
	}
	free(tmp_tail);
	tmp_tail = NULL;
}

void free_block(t_list *lst, int fd) //because I use a static t_list, my first mod is not malloced. so I dont need to free it
{
	t_list	*tmp_head;
	t_list	*tmp_tail;

	if (!lst)
		return ;
	if (lst->fd == fd)
		tmp_tail = lst;
	else
	{
		tmp_head = lst;
		tmp_tail = tmp_head->next;
		while (tmp_tail->fd != fd)
		{
			tmp_head = tmp_head->next;
			tmp_tail = tmp_tail->next;
		}
		tmp_head->next = tmp_tail->next;
	}
	if (tmp_tail->content)
	{
		free(tmp_tail->content);
		tmp_tail->content = NULL;
	}
	free(tmp_tail);
	tmp_tail = NULL;
}
*//*
void free_block(t_list **lst, int fd)
{
	t_list	*tmp_head;
	t_list	*tmp_tail;

	if (!(*lst))
		return ;
	if ((*lst)->fd == fd)
		tmp_tail = (*lst);
	else
	{
		tmp_head = (*lst);
		tmp_tail = tmp_head->next;
		while (tmp_tail->fd != fd)
		{
			tmp_head = tmp_head->next;
			tmp_tail = tmp_tail->next;
		}
		tmp_head->next = tmp_tail->next;
	}
	if (tmp_tail->content)
	{
		free(tmp_tail->content);
		tmp_tail->content = NULL;
	}
	free(tmp_tail);
	tmp_tail = NULL;
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
		if (c_lst->position == BUFFER_SIZE)
		{
			ret = read (c_lst->fd, c_lst->buff, BUFFER_SIZE);
			c_lst->position = 0;
		}
	}
	while (1)
	{
//		printf("round %d content = %s\n", i, c_lst->content);
		printf("round %d buff = %s\n", i, c_lst->buff);
//		printf("round %d position = %zu\n\n", i++, c_lst->position);
		if (c_lst->buff[0] != '\0')
			c_lst->content = ft_strjoinfree_s1(c_lst->content, c_lst->buff, c_lst, c_lst->position);
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



char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*c_lst;

	c_lst = ft_lstchr_feat_addback(c_lst &lst, fd);//find correct fd in the list

	printf("adresse if lst in main fonction : [%p]\n", lst);
	printf("adresse if lst in main fonction : [%p]\n", c_lst);
	if (c_lst && c_lst->content)
	{
		free(c_lst->content);
		c_lst->content = NULL;
		if (c_lst->position == BUFFER_SIZE)
		{
			if (!read(c_lst->fd, c_lst->buff, BUFFER_SIZE)) // read again coz position is at buffer size;
				free(c_lst);// need to free_block instead;
			else
				c_lst->position = 0;//reset position coz position is at buffer size. 
		}
	}
//	printf("working on fd nbr %d\n", c_lst->fd);
//	ft_print_list_result(&lst);
	printf("working of fd %d\n", fd);
	if (c_lst)
		build_content(c_lst);
//	ft_print_current_lst(c_lst);
	return (c_lst->content);
}

t_list	*ft_lst_init_addback(t_list *lst, int fd)
{
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp = tmp->next;
	tmp->fd = fd;
	tmp->content = NULL;
	while (++i < BUFFER_SIZE + 1)
		tmp->buff[i] = '\0';
	tmp->position = 0;
	tmp->next = NULL;
	return (tmp);
}
*/

size_t	ft_strlen_gnl(const char *str, t_list *c_lst, int on_switch)
	//switch on = case buff, save position and return char to print
{
	size_t	start;
	size_t	index;

	if (!str)
		return (0);//protection
	start = 0;
	if (on_switch)
	{
		start = c_lst->position;
		c_lst->position = 0;
	}
	index = start;
	while (str[index])
	{
		if (str[index] == '\n')
		{
			if (on_switch)
				c_lst->position = index + 1; //on_switch : there is a \n in buff. save following position
			else
				return (0); // case there is a \n in the content.
			return (index - start + 1); // on_switch : return number of char to copie into malloc
		}
		index++;
	}
	return (index - start); // case no \n. return the correct value.
}

char	*ft_strjoinfree_s1(t_list *c_lst, size_t position)	// here position is not a pointer
{
	size_t		len_s1;
	size_t		len_s2;
	int			index;
	char		*joined_str;

	if (!c_lst->content && !c_lst->buff[0])
		return (NULL);
	len_s1 = ft_strlen_gnl(c_lst->content, c_lst, 0);
	len_s2 = ft_strlen_gnl(c_lst->buff, c_lst, 1);//this function change the c_lst->positon if there is a \n
	index = -1;
	joined_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	while (++index <(int)len_s1)
		*(joined_str++) = c_lst->content[index];
	index = -1;
	while (++index < (int)len_s2)
		*(joined_str++) = c_lst->buff[position++];
	*(joined_str) = '\0';
	if (c_lst->content)
	{
	//	printf("freeing address s1 in strjoinfree  %p\n", c_lst->content);
		free(c_lst->content);
	}
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
	printf("->position = %zu\n", c_lst->position);
	printf("->buffer = %s\n", c_lst->buff);
}

void	ft_print_lst_address(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("fd %d, adress = %p\n", tmp->fd, tmp);
		tmp = tmp->next;
	}
}

/*************************** chain list fuction*****************************/
void	free_list(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (tmp->content)
		{
	//		printf("free tmp->content = %p in free_list\n", tmp->content);
			free(tmp->content);
			tmp->content = NULL;
		}
		free(tmp);
	//	printf("free in free_listadress = %p\n", tmp);
		tmp = NULL;
	}
}
/*
void free_block(t_list **lst, int fd)
{
	t_list	*tmp_1;
	t_list	*tmp_2;

	if (!(*lst))
		return ;
	tmp_2 = *lst;
	if ((*lst)->fd != fd)
	{
		while (tmp_2->fd != fd)
		{	
			tmp_1 = tmp_2;
			tmp_2 = tmp_2->next;
		}
		tmp_1->next = tmp_2->next;
	}
	if (tmp_2->content)
	{
		printf("free tmp_2->content = %p in free_block\n", tmp_2->content);
		free(tmp_2->content);
	}
	printf("free in free_block adress = %p\n", tmp_2);
	free(tmp_2);
	if ((*lst) == tmp_2)
		*lst = NULL;
}
*/
void free_block(t_list **lst, t_list **c_lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp != *c_lst)
	{
	while (tmp->next != *c_lst)
		tmp = tmp->next;
	}
	tmp->next = (*c_lst)->next;
	free(*c_lst);
//	if ((*lst) == *c_lst)
		*lst = NULL;
	*c_lst = NULL;
}
/*
void	build_content(t_list *c_lst)
{
	int	ret;

	ret = 0;
	if (c_lst && c_lst->content)
	{
		free(c_lst->content);
		c_lst->content = NULL;
		if (c_lst->position == BUFFER_SIZE)
		{
			if (!read(c_lst->fd, c_lst->buff, BUFFER_SIZE)) // read again coz position is at buffer size;
				free(c_lst);// need to free_block instead;
			else
				c_lst->position = 0;//reset position coz position is at buffer size. 
		}
	}
	while (1)
	{
		if (c_lst->buff[0] != '\0')//not sure about this line(case empty file, or only with \0 ?)
		c_lst->content = ft_strjoinfree_s1(c_lst, c_lst->position);
		if (c_lst->content && !ft_strlen_gnl(c_lst->content, c_lst, 0))
		{
		//	printf("using this breakin exit coz there is a \n in content\n");
			break ;
		}
		ret = read (c_lst->fd, c_lst->buff, BUFFER_SIZE);
		printf("ret = %d\n", ret);
		if (ret == BUFFER_SIZE)
			c_lst->buff[BUFFER_SIZE] = '\0';
		else
			c_lst->buff[ret] = '\0';
		if (!ret)
		{
			printf("I am gonna break\n");
			break ;
		}
	}
}
*/
int	ft_strchr_booleen(const char *str, char c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return (1);
		str++;
	}
	return (0);
}

void	build_content(t_list **lst, t_list **c_lst)
{
	int	ret;

	ret = 0;
	if (*c_lst && (*c_lst)->position >= BUFFER_SIZE)
	{
		(*c_lst)->position = 0;
		(*c_lst)->buff[(*c_lst)->position] = '\0';
	}
	if ((*c_lst) && (*c_lst)->buff[(*c_lst)->position])
		(*c_lst)->content = ft_strjoinfree_s1((*c_lst), (*c_lst)->position);
	if ((*c_lst) && (*c_lst)->position == 0)
		ret = read((*c_lst)->fd, (*c_lst)->buff,BUFFER_SIZE);
	if (ret <= 0)
	{
		if (ret == 0 && (*c_lst)->buff[(*c_lst)->position] == '\0' && !(*c_lst)->content)
			free_block(lst, c_lst);
		else if (ret == -1)
			free_list(lst);
		return ;
	}
	(*c_lst)->buff[ret] = '\0';
	if ((*c_lst)->content && ft_strchr_booleen((*c_lst)->content, '\n'))// might have to use ft_strlen here
		return ;
	else if (*c_lst)
		build_content(lst, c_lst);
}

/*
void	build_content(t_list **lst, t_list *c_lst)
{
	int	ret;

	ret = 0;
	if (c_lst && c_lst->position >= BUFFER_SIZE)
	{
		c_lst->position = 0;
		c_lst->buff[c_lst->position] = '\0';
	}
	if (c_lst && c_lst->buff[c_lst->position])
		c_lst->content = ft_strjoinfree_s1(c_lst, c_lst->position);
	if (c_lst && c_lst->position == 0)
		ret = read(c_lst->fd, c_lst->buff,BUFFER_SIZE);
	if (ret <= 0)
	{
		if (ret == 0 && c_lst->buff[c_lst->position] == '\0' && !c_lst->content)
			free_block(lst, c_lst);
		else if (ret == -1)
			free_list(lst);
		return ;
	}
	c_lst->buff[ret] = '\0';
	if (c_lst->content && ft_strchr_booleen(c_lst->content, '\n'))// might have to use ft_strlen here
		return ;
	else if (c_lst)
		build_content(lst, c_lst);
}
*/

t_list	*ft_lst_init_addback(t_list **lst, int fd)
{
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = (*lst);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->next = malloc(sizeof(t_list));
		printf("allocation adress = %p\n", tmp->next);
		tmp = tmp->next;
		if (!tmp)
			return (NULL);
	}
	else
	{
		tmp = malloc(sizeof(t_list));
		printf("allocation adress in ft_lst_init_addback= %p\n", tmp);
	}
	tmp->fd = fd;
	tmp->content = NULL;
	while (++i < BUFFER_SIZE + 1)
		tmp->buff[i] = '\0';
	tmp->position = 0;
	tmp->next = NULL;
	if (!*lst)
		*lst = tmp;
	return (tmp);
}

/*********************************gnl******************************/

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*c_lst;

	if (BUFFER_SIZE <= 0)
		return NULL;
	c_lst = lst;
	while (c_lst && c_lst->fd != fd)
		c_lst = c_lst->next;
	if (!c_lst)
		c_lst = ft_lst_init_addback(&lst, fd);
	if (lst && c_lst && c_lst->content)
	{
		//printf("free c_lst->content = %p in get_next_line\n", c_lst->content);
		//free(c_lst->content);
		c_lst->content = NULL;
	}
	build_content(&lst, &c_lst);
//	ft_print_lst_address(&lst);
	if (lst && c_lst)
		return (c_lst->content);
	else if (c_lst)
		free_block(&lst, &c_lst);
		return NULL;
	
}