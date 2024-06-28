/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:16:53 by joao-rde          #+#    #+#             */
/*   Updated: 2024/06/26 16:45:11 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	while_tests(int fd1, int fd2) {

	char *line;
	while ((line = get_next_line(fd1)) != NULL) {
		printf("%s", line);
		free(line);
	}
	
	while ((line = get_next_line(fd2)) != NULL) {
		printf("%s", line);
		free(line);
	}
	
}

static void	print_next_line(int fd) {
	char *line;

	if(!fd)
		return;
	line = get_next_line(fd);
	if(!line)
	{
		printf("|NULL|\n");
		return ;
	}
	printf("|%s|\n", line);
	free(line);
}

static void	manual_tests(int fd1) {

	print_next_line(fd1);
	print_next_line(fd1);
		char *temp;
		do {
			temp = get_next_line(fd1);
			free(temp);
		} while (temp != NULL);
	print_next_line(fd1);


}


int	main(void) {
	char *name1 = "read_error.txt";
	char *name2 = "read_error.txt";

	int fd1 = open(name2, O_RDONLY);
	int fd2 = open(name2, O_RDONLY);
	
	printf("\n--- manual tests ---\n");
	printf("--------------------\n");
	manual_tests(fd2);
	printf("\n--- while tests ---\n");
	printf("--------------------\n");
	while_tests(fd2, fd1);

	close(fd2);

	return (0);
}
