/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahiguera <ahiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:20:41 by ahiguera          #+#    #+#             */
/*   Updated: 2023/11/30 15:00:18 by ahiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*gn_getline(char *line, char *buffer)
{
	char	*result;
	size_t	line_len;
	size_t	buf_len;

	line_len = gn_strlen(line);
	buf_len = 0;
	while (buffer[buf_len] != '\n' && buffer[buf_len] != '\0')
		buf_len++;
	if (buffer[buf_len] == '\n')
		buf_len += 1;
	result = (char *)malloc(sizeof(char) * (line_len + buf_len + 1));
	if (result == NULL)
		return (NULL);
	gn_strncpy(result, line, line_len);
	gn_strncpy(result + line_len, buffer, buf_len);
	result[line_len + buf_len] = '\0';
	return (gn_free(line), result);
}

static void	gn_saverest(char *buffer)
{
	size_t	buf_len;
	size_t	rest_len;

	buf_len = 0;
	while (buffer[buf_len] != '\n' && buffer[buf_len] != '\0')
		buf_len++;
	if (buffer[buf_len] == '\n')
	{
		buf_len += 1;
		rest_len = gn_strlen(buffer + buf_len);
		gn_strncpy(buffer, buffer + buf_len, rest_len);
		buffer[rest_len] = '\0';
	}
	else
		buffer[0] = '\0';
}

static char	*gn_readline(int fd, char *buffer)
{
	char	*line;
	ssize_t	bytes_read;

	line = gn_getline(NULL, buffer);
	if (line == NULL)
		return (NULL);
	bytes_read = 1;
	while (!gn_strchr(line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && gn_strlen(line) == 0))
			return (buffer[0] = '\0', gn_free(line), NULL);
		buffer[bytes_read] = '\0';
		line = gn_getline(line, buffer);
	}
	gn_saverest(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		buffer[4096][BUFFER_SIZE + 1];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = gn_readline(fd, buffer[fd]);
	return (line);
}
