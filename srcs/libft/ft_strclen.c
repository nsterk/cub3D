/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strclen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 12:26:39 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/01 19:48:09 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strclen(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (*s != '\0')
		{
			if (*s != c)
				i++;
			s++;
		}
	}
	return (i);
}
