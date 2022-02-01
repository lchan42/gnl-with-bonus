/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:05:46 by lchan             #+#    #+#             */
/*   Updated: 2022/02/01 19:40:20 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
/*
int	main(int ac, char **av)
{
	int index = -1;
	char *str;
	int fd;
	(void) ac;
	(void) av;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("open error\n");
		return (0);
	}
	str = NULL;
	while (++index < 10)
	{
		str = get_next_line(fd);
		printf("call %d : %s",index, str); 
		free(str);
	}
	if (close(fd) == -1)
		printf("close error\n");
//	system("leaks a.out");
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
	while (str) 
	{
		str = get_next_line(fd);
		printf("str = %s", str); 
	}
//	printf("%s", get_next_line(fd2)); 
//	printf("%s", get_next_line(fd2)); 
//	printf("%s", get_next_line(fd)); 
//	printf("%s", get_next_line(fd)); 
	if (close(fd) == -1 || close(fd2) == -1)
		printf("close error\n");
	return (0);
}

//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt
//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt test3.txt testnull.txt | cat -e
