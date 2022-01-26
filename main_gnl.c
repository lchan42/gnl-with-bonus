/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:05:46 by lchan             #+#    #+#             */
/*   Updated: 2022/01/26 18:27:57 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	main(int ac, char **av)
{
	int fd;
	int	fd2;
	int	fd3;
	(void) ac;

	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	fd3 = open(av[3], O_RDONLY);
	if (fd == -1 || fd2 == -1 || fd3 == -1)
	{
		printf("open error\n");
		return (0);
	}
//	else
//		printf("fd = %d, open success\n", fd); printf("fd2 = %d, open success\n", fd2);
	printf("\n\n*****************First call of gnl with %s\n", av[1]); printf("	fd = %d\n", fd);
	get_next_line(fd); 
/*	printf("\n\n*****************Second call of gnl\n"); printf("	fd = %d\n", fd);
	get_next_line(fd); 
	printf("\n\n*****************Third call of gnl with %s\n", av[2]); printf("	fd = %d\n", fd2);
	get_next_line(fd2);
	printf("\n\n*****************fourth call of gnl qith %s\n", av[3]); printf("	fd = %d\n", fd3);
	get_next_line(fd3);*/
	if (close(fd) == -1 || close(fd2) == -1)
		printf("close error\n");
	return (0);
}

//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt
//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt test3.txt | cat -e
