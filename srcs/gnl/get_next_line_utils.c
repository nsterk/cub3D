/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 20:59:45 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/03 01:48:24 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			i++;
	}
	return (i);
}

void	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*gnl_strndup(const char *src, size_t n)
{
	char	*str;

	str = malloc(sizeof(*str) * (n + 1));
	if (!str)
		return (NULL);
	gnl_strlcpy(str, src, n + 1);
	return (str);
}

char	*gnl_strjoin(const char *s1, const char *s2, size_t len_s2)
{
	size_t	len_s1;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gnl_strndup(s2, len_s2));
	len_s1 = gnl_strlen(s1);
	str = malloc(sizeof(*str) * (len_s1 + len_s2 + 1));
	if (!str)
		str = NULL;
	else
	{
		gnl_strlcpy(str, s1, len_s1 + 1);
		gnl_strlcpy(str + len_s1, s2, len_s2 + 1);
	}
	free((char *)s1);
	return (str);
}
