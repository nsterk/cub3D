/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 20:01:20 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/20 14:57:36 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	first_char(char *str)
{
	while (*str && is_space(str))
		str++;
	return (*str);
}

int	is_space(char *s)
{
	return (*s == '\t' || *s == '\n' || *s == '\f' || \
	 *s == '\r' || *s == '\v' || *s == ' ');
}

int	set_status(t_status *status, t_status num)
{
	*status = num;
	return (0);
}
