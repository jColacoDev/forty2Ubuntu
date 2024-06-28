/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:46:26 by joao-rde          #+#    #+#             */
/*   Updated: 2024/06/21 19:16:30 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	get_len_of_line(const char *buffer)
{
	size_t	len;

	len = 0;
	while (buffer[len] != '\n' && buffer[len] != '\0')
		len++;
	if (buffer[len] == '\n')
		len++;
	return (len);
}

static ssize_t	get_read(int fd, char **buffer)
{
	ssize_t	read_length;

	free(*buffer);
	*buffer = malloc(sizeof(**buffer) * (BUFFER_SIZE + 1));
	if (*buffer == NULL)
		return (0);
	read_length = read(fd, *buffer, BUFFER_SIZE);
	if (read_length <= 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	else
		(*buffer)[read_length] = '\0';
	return (read_length);
}

static int	get_line_aux(char **buffer, ssize_t *read_length, int fd)
{
	if (ft_strlen(*buffer) == 0)
	{
		*read_length = get_read(fd, buffer);
		if (*read_length <= 0)
			return (0);
	}
	return (1);
}

static char	*get_line(char **buffer, int fd, int *nl_flag)
{
	ssize_t	read_length;
	size_t	line_length;
	char	*line;
	char	*buff_aux;

	if (!get_line_aux(buffer, &read_length, fd))
		return (NULL);
	line_length = get_len_of_line(*buffer);
	if (line_length == 0)
		return (NULL);
	*nl_flag = (*buffer)[line_length - 1] == '\n' ? 1 : 0;
	line = malloc(line_length + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, *buffer, line_length + 1);
	buff_aux = ft_strdup(*buffer + line_length);
	if (buff_aux == NULL)
	{
		free(line);
		return (NULL);
	}
	ft_strlcpy(*buffer, buff_aux, ft_strlen(buff_aux) + 1);
	free(buff_aux);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	int			nl_flag;
	char		*line_old;
	char		*line;
	char		*new_line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	nl_flag = 0;
	line = get_line(&buffer[fd], fd, &nl_flag);
	if (!line)
		return (NULL);
	while (nl_flag == 0)
	{
		new_line = get_line(&buffer[fd], fd, &nl_flag);
		if (!new_line)
			return (line);
		line_old = line;
		line = ft_strjoin(line, new_line);
		free(new_line);
		free(line_old);
		if (!line)
			return (NULL);
	}
	return (line);
}
