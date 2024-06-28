/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:41:37 by joao-rde          #+#    #+#             */
/*   Updated: 2024/06/21 19:21:25 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	get_len_of_line(char *buffer)
{
	size_t	len;

	len = 0;
	while (buffer[len] != '\n' && buffer[len] != '\0')
		len++;
	if (buffer[len] == '\n')
		len++;
	return (len);
}

static ssize_t	get_read(int fd, char *buffer)
{
	ssize_t	read_length;

	read_length = read(fd, buffer, BUFFER_SIZE);
	if (read_length > 0)
		buffer[read_length] = 0;
	else
		buffer[0] = 0;
	return (read_length);
}

static int	get_line_aux(char *buffer, int fd)
{
	ssize_t	read_length;

	if (ft_strlen(buffer) == 0)
	{
		read_length = get_read(fd, buffer);
		if (read_length <= 0)
			return (0);
	}
	return (-1);
}

static char	*get_line(char *buffer, int fd, int *nl_flag)
{
	size_t	line_length;
	char	*line;
	char	*buff_aux;

	if (!get_line_aux(buffer, fd))
		return (NULL);
	line_length = get_len_of_line(buffer);
	if (buffer[line_length - 1] == '\n')
		*nl_flag = 1;
	line = malloc(line_length + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, buffer, line_length + 1);
	buff_aux = ft_strdup((buffer) + line_length);
	if (buff_aux == NULL)
	{
		free(line);
		return (NULL);
	}
	ft_strlcpy(buffer, buff_aux, ft_strlen(buff_aux) + 1);
	free(buff_aux);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			nl_flag;
	char		*current_line;
	char		*new_line;
	char		*previous_line;

	if (fd < 0)
		return (NULL);
	nl_flag = 0;
	current_line = get_line(buffer, fd, &nl_flag);
	if (current_line == NULL)
		return (NULL);
	while (nl_flag == 0)
	{
		new_line = get_line(buffer, fd, &nl_flag);
		if (new_line == NULL)
			return (current_line);
		previous_line = current_line;
		current_line = ft_strjoin(current_line, new_line);
		free(new_line);
		free(previous_line);
	}
	return (current_line);
}
