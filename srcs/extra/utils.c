/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 20:01:20 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/11 14:50:45 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	first_char(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (*str);
}

int	is_space(char *s)
{
	return (*s == '\t' || *s == '\n' || *s == '\f' || \
	 *s == '\r' || *s == '\v' || *s == ' ');
}
