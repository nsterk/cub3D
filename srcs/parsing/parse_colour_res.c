/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour_res.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:21:29 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/19 16:50:33 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	parse_res(t_data *data, char *line)
{
	int	i;

	i = 0;
	if (data->res.x || data->res.y)
		return (set_status(&data->status, CONFIG_ERROR));
	line = (char *)ft_skipspace(line);
	if (!ft_isdigit(*line))
		return (0);
	data->res.x = ft_atoi(line);
	while (ft_isdigit(line[i]))
		i++;
	line = (char *)ft_skipspace(line + i);
	if (!ft_isdigit(*line))
		return (0);
	data->res.y = ft_atoi(line);
	return (validate_res(data, line + i));
}

int	colour(t_data *data, char *line)
{
	if (*line == 'C')
	{
		if (data->ceiling)
			return (set_status(&data->status, CONFIG_ERROR));
		else
			return (parse_colour(&data->ceiling, line + 1));
	}
	if (data->floor)
		return (set_status(&data->status, CONFIG_ERROR));
	return (parse_colour(&data->floor, line + 1));
}

int	parse_colour(int *colour, char *line)
{
	char	**str;
	int		i;
	int		R;
	int		G;
	int		B;

	str = ft_split(line, ',');
	if (!str)
		return (0);
	i = str_array_size(str);
	if (i == 3)
	{
		R = ft_atoi(str[0]);
		G = ft_atoi(str[1]);
		B = ft_atoi(str[2]);
	}
	free_alloc(str, i);
	if (R < 0 || G < 0 || B < 0
		|| R > 255 || G > 255 || B > 255)
		return (0);
	*colour = create_trgb(0, R, G, B);
	return (1);
}
