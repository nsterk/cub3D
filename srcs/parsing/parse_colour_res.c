/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour_res.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:21:29 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/08 18:57:48 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

int	parse_res(t_file *file, char *line)
{
	size_t	i;

	i = 0;
	line = (char *)ft_skipspace(line);
	if (!ft_isdigit(*line))
		return (0);
	file->res.x = ft_atoi(line);
	while (ft_isdigit(line[i]))
		i++;
	line = (char *)ft_skipspace(line + i);
	if (!ft_isdigit(*line))
		return (0);
	file->res.y = ft_atoi(line);
	return (1);
}

int	colour(t_file *file, char *line)
{
	if (*line == 'C')
		return (parse_colour(&file->ceiling, line + 1));
	return (parse_colour(&file->floor, line + 1));
}

int	parse_colour(t_colour *colour, char *line)
{
	char	**str;

	str = ft_split(line, ',');
	if (!str)
		return (0);
	colour->R = ft_atoi(str[0]);
	colour->G = ft_atoi(str[1]);
	colour->B = ft_atoi(str[2]);
	if (colour->R < 0 || colour->G < 0 || colour->B < 0
		|| colour->R > 255 || colour->G > 255
		|| colour->B > 255)
	{
		ft_free_array(str);
		printf("Invalid ceiling or floor colour\n");
		return (0);
	}
	return (1);
}