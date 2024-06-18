/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:16:53 by joao-rde          #+#    #+#             */
/*   Updated: 2024/06/18 18:17:25 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	printf("BUFFER_SIZE: %d", BUFFER_SIZE);
	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		write(1, line, ft_strlen(line));
		free(line);
	}
	return (0);
}
