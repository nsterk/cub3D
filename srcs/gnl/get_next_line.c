/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 21:02:52 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/03 01:47:39 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	has_newline(char *buffer)
{
	size_t	i;

	i = 0;
	if (buffer)
	{
		while (buffer[i])
		{
			if (buffer[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

static char	*adjust_buffer(char *buffer)
{
	size_t	offset;

	if (!buffer)
		return (NULL);
	offset = 0;
	while (buffer[offset] && buffer[offset] != '\n')
		offset++;
	if (buffer[offset])
		offset++;
	gnl_strlcpy(buffer, buffer + offset, gnl_strlen(buffer) + 1);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	size_t	len;
	char	*str;

	if (!buffer)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
	{
		free(buffer);
		return (NULL);
	}
	gnl_strlcpy(str, buffer, len + 1);
	return (str);
}

static int	fill_buffer(int fd, char **buffer)
{
	char	temp_buffer[BUFFER_SIZE + 1];
	int		ret;

	ret = 1;
	while (!has_newline(*buffer) && ret)
	{
		ret = read(fd, temp_buffer, BUFFER_SIZE);
		if (ret < 0)
		{
			if (*buffer)
				free(*buffer);
			return (-1);
		}
		temp_buffer[ret] = '\0';
		*buffer = gnl_strjoin(*buffer, temp_buffer, ret);
		if (!*buffer)
			return (-1);
	}
	if (ret > 0)
		ret = 1;
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*buffer;
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	ret = fill_buffer(fd, &buffer);
	if (ret == -1)
		return (-1);
	*line = get_line(buffer);
	if (!*line)
		return (-1);
	buffer = adjust_buffer(buffer);
	if (ret == 0 && buffer)
		free(buffer);
	return (ret);
}
