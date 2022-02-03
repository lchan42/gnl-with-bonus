/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:05:46 by lchan             #+#    #+#             */
/*   Updated: 2022/01/31 17:27:45 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
/*
int	main(int ac, char **av)
{
	int index = -1;
	int fd;
	(void) ac;
	(void) av;

	fd = open("testnull.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("open error\n");
		return (0);
	}
	while (++index < 10)
		printf("call %d : %s",index,  get_next_line(fd)); 
	if (close(fd) == -1)
		printf("close error\n");
	return (0);
}
//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=8 && ./a.out
//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=8 && lldb a.out

*/
int	main(int ac, char **av)
{
	int index = -1;
	char	*str =  "a";
	int fd;
	int	fd2;
	int	fd3;
	int fd4;
	(void) ac;

	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	fd3 = open(av[3], O_RDONLY);
	fd4 = open(av[4], O_RDONLY);
	if (fd == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1)
	{
		printf("open error\n");
		return (0);
	}
//	else
//		printf("fd = %d, open success\n", fd); printf("fd2 = %d, open success\n", fd2);
//	printf("\n\n*****************First call of gnl with %s\n", av[1]); printf("	fd = %d\n", fd);
	while (str) 
	{
		str = get_next_line(fd4);
		printf("%s", str); 
//		printf("%s", get_next_line(fd2)); 
//		printf("%s", get_next_line(fd2)); 
//		printf("%s", get_next_line(fd3));
	}
//	printf("%s", get_next_line(fd2)); 
//	printf("%s", get_next_line(fd2)); 
//	printf("%s", get_next_line(fd)); 
//	printf("%s", get_next_line(fd));
	free(str);
	if (close(fd) == -1 || close(fd2) == -1)
		printf("close error\n");
	return (0);
}

//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt
//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt test3.txt | cat -e
