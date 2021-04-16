/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 18:26:56 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/15 19:39:08 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	parse_tex(t_data *data, char *line)
{
	if (*line == 'N')
	{
		data->tex[0].path = ft_strtrim(line + 2, " ");
		if (!data->tex[0].path)
			return (0);
	}
	else if (*line == 'E')
	{
		data->tex[1].path = ft_strtrim(line + 2, " ");
		if (!data->tex[1].path)
			return (0);
	}
	else if (*line == 'S')
	{
		data->tex[2].path = ft_strtrim(line + 2, " ");
		if (!data->tex[2].path)
			return (0);
	}
	else if (*line == 'W')
	{
		data->tex[3].path = ft_strtrim(line + 2, " ");
		if (!data->tex[3].path)
			return (0);
	}
	return (1);
}