/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 19:00:03 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/03 01:40:39 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_split(char **rstr, int len)
{
	while (len)
	{
		len--;
		free(rstr[len]);
	}
	free(rstr);
	return (NULL);
}

static char	**make_substrs(char **rstr, char const *s, char c, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (*s == (unsigned char)c)
		s++;
	while (j < len)
	{
		i = 0;
		while (s[i] != '\0' && s[i] != (unsigned char)c)
			i++;
		rstr[j] = (char *)malloc(sizeof(char) * (i + 1));
		if (!rstr[j])
			return (free_split(rstr, (int)j));
		ft_strlcpy(rstr[j], s, (i + 1));
		while (s[i] == (unsigned char)c)
			i++;
		s += i;
		j++;
	}
	rstr[j] = NULL;
	return (rstr);
}

static size_t	find_amount(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == '\0')))
			len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**rstr;
	size_t	len;

	if (!s)
		return (NULL);
	len = find_amount(s, c);
	rstr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!rstr)
		return (NULL);
	rstr = make_substrs(rstr, s, c, len);
	return (rstr);
}
