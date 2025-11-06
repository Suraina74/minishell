/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:01:18 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/05 15:57:16 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*new_line(char **line)
{
	char	*remainder;
	char	*newline;
	char	*new_line_ch;

	new_line_ch = gn_strchr(*line, '\n');
	if (new_line_ch != NULL)
	{
		newline = gn_substr(*line, 0, (gn_strlen(*line) \
- gn_strlen(new_line_ch)) + 1);
		remainder = gn_strdup(&new_line_ch[1]);
		free(*line);
		*line = NULL;
		if (newline == NULL || remainder == NULL)
			return (free(newline), free(remainder), NULL);
		*line = remainder;
		return (newline);
	}
	newline = *line;
	*line = NULL;
	return (newline);
}

static char	*join_line(char *line, char *buffer)
{
	char	*temp;

	temp = line;
	line = gn_strjoin(line, buffer);
	free(temp);
	return (line);
}

static char	*fill_line(int fd, char *buffer, char *line)
{
	int		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1 || (bytes_read == 0 \
&& line == NULL) || (bytes_read == 0 && line[0] == '\0'))
	{
		if (line != NULL)
			free(line);
		return (NULL);
	}
	if (line == NULL)
		line = gn_strdup("");
	if (line == NULL)
		return (NULL);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		line = join_line(line, buffer);
		if (line == NULL)
			return (NULL);
		if (gn_strchr(buffer, '\n') != NULL)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*newline;
	static char	*line;
	static char	buffer[BUFFER_SIZE + 1] = {0};

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = fill_line(fd, buffer, line);
	if (line == NULL)
		return (NULL);
	newline = new_line(&line);
	return (newline);
}
