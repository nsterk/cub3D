/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 18:26:56 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/13 15:56:34 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	parse_tex(t_tex *tex, char *line)
{
	if (*line == 'N')
	{
		tex[0]->path = ft_strtrim(line + 2, " ");
		if (!tex[0]->path)
			return (0);
	}
	else if (*line == 'E')
	{
		tex[1]->path = ft_strtrim(line + 2, " ");
		if (!tex[1]->path)
			return (0);
	}
	else if (*line == 'S')
	{
		tex[2]->path = ft_strtrim(line + 2, " ");
		if (!tex[2]->path)
			return (0);
	}
	else if (*line == 'W')
	{
		tex[3]->path = ft_strtrim(line + 2, " ");
		if (!tex[3]->path)
			return (0);
	}
	return (1);
}
