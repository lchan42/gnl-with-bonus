/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:05:46 by lchan             #+#    #+#             */
/*   Updated: 2022/02/03 18:14:17 by lchan            ###   ########.fr       */
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
	int	fd5;
	(void) ac;

	fd = open(av[1], O_RDONLY);
	fd2 = open("test.txt", O_RDONLY);
	fd3 = open("test2.txt", O_RDONLY);
	fd4 = open("test3.txt", O_RDONLY);
	fd5 = open("gnlTester/files/empty", O_RDWR);

	if (fd == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1 || fd5 == -1)
	{
		printf("open error\n");
		return (0);
	}
//	else
//		printf("fd = %d, open success\n", fd); printf("fd2 = %d, open success\n", fd2);
//	printf("\n\n*****************First call of gnl with %s\n", av[1]); printf("	fd = %d\n", fd);
//	while (str) 
//	{
		str = get_next_line(fd);
		printf("%s", str); 
		str = get_next_line(fd);
		printf("%s", str); 
//	}
	if (str)
		free(str);
	if (close(fd) == -1 || close(fd2) == -1)
		printf("close error\n");
	return (0);
}

//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt
//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt test3.txt | cat -e
//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt test3.txt | cat -e

