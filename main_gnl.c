/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:05:46 by lchan             #+#    #+#             */
/*   Updated: 2022/01/25 21:04:25 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	main(int ac, char **av)
{
	int fd;
	int	fd2;
	(void) ac;

	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	if (fd == -1 || fd2 == -1)
	{
		printf("open error\n");
		return (0);
	}
//	else
//		printf("fd = %d, open success\n", fd); printf("fd2 = %d, open success\n", fd2);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd2);
	if (close(fd) == -1 || close(fd2) == -1)
		printf("close error\n");
	return (0);
}

//gcc -g3 -fsanitize=address main_gnl.c get_next_line.c -D BUFFER_SIZE=10 && ./a.out test.txt test2.txt
