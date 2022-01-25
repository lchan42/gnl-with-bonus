/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:58:12 by lchan             #+#    #+#             */
/*   Updated: 2022/01/25 21:04:30 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*ft_strjoinfree(const char *s1, const char *s2)
{
	int		len_s1;
	int		len_s2;
	int		index;
	char	*joined_str;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	index = -1;
	joined_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	while (++index < len_s1)
		*(joined_str++) = s1[index];
	index = -1;
	while (++index < len_s2)
		*(joined_str++) = s2[index];
	*(joined_str) = '\0';
//	free(s1);
//	free(s2);
	return (joined_str - (len_s1 + len_s2));
}

void	del_print_lst_content_and_address(t_list *lst)
{
	printf("fd = %d\n", lst->fd);
	printf("content = %s\n", lst->content);
}

t_list	*ft_lstchr_feat_lstnew(t_list **lst, int fd)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->fd == fd)
				return (tmp);
			if (tmp->next)
				tmp = tmp->next;
		}
	}
	if (!*lst || tmp == NULL)
	{
		tmp2 = malloc(sizeof(t_list));
		if (!tmp2)
			return (NULL);
		tmp2->fd = fd;
		tmp2->content = NULL;
		tmp2->next = NULL;
		if (!*lst)
			(*lst) = tmp2;
		else
			tmp->next = tmp2;
		return (tmp2);
	}
	return (NULL);
}

void	ft_print_list_result(t_list *alst)
{

	int	i;

	i = 0;
	printf("\nthis is the current list whole content:\n");
	while (alst)
	{
		printf("t_list nbr %d ->fd = %d\n", i++, alst->fd);
		alst = alst->next;
	}
}

char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	*lst;
	t_list			*current_lst;
//	static tab[MAX_OPEN];

	next_line = NULL;
	current_lst = ft_lstchr_feat_lstnew(&lst, fd);
	printf("working on fd nbr %d\n", current_lst->fd);
	ft_print_list_result(lst);
	return (next_line);
}
