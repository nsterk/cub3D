/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour_res.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:21:29 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/22 16:50:19 by nsterk        ########   odam.nl         */
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
		return (set_status(&data->status, CONFIG_ERROR));
	data->res.x = ft_atoi(line);
	while (ft_isdigit(line[i]))
		i++;
	line = (char *)ft_skipspace(line + i);
	if (!ft_isdigit(*line))
		return (set_status(&data->status, CONFIG_ERROR));
	data->res.y = ft_atoi(line);
	return (validate_res(data, line + i));
}

int	colour(t_data *data, char *line)
{
	if (*line == 'C')
	{
		if (data->ceiling != -1)
			return (set_status(&data->status, CONFIG_ERROR));
		else
			return (parse_colour(&data->status, &data->ceiling, line + 1));
	}
	if (data->floor != -1)
		return (set_status(&data->status, CONFIG_ERROR));
	return (parse_colour(&data->status, &data->floor, line + 1));
}

int	parse_colour(t_status *status, int *colour, char *line)
{
	char	**str;
	int		i;
	int		R;
	int		G;
	int		B;

	str = ft_split(line, ',');
	if (!str)
		return (set_status(status, MALLOC_ERROR));
	i = str_array_size(str);
	if (i == 3)
	{
		R = ft_atoi(str[0]);
		G = ft_atoi(str[1]);
		B = ft_atoi(str[2]);
	}
	free_str_array(str, i);
	if (R < 0 || G < 0 || B < 0
		|| R > 255 || G > 255 || B > 255)
		return (0);
	*colour = create_trgb(0, R, G, B);
	return (1);
}
