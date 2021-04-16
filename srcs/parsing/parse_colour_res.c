/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour_res.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:21:29 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/16 13:43:34 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	parse_res(t_data *data, char *line)
{
	size_t	i;

	i = 0;
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
	return (1);
}

int	colour(t_data *data, char *line)
{
	if (*line == 'C')
		return (parse_colour(&data->ceiling, line + 1));
	return (parse_colour(&data->floor, line + 1));
}

int	parse_colour(int *colour, char *line)
{
	char	**str;
	int		i;
	int		R;
	int		G;
	int		B;

	i = 0;
	str = ft_split(line, ',');
	if (!str)
		return (0);
	R = ft_atoi(str[0]);
	G = ft_atoi(str[1]);
	B = ft_atoi(str[2]);
	if (R < 0 || G < 0 || B < 0
		|| R > 255 || G > 255 || B > 255)
	{
		ft_free_array(str);
		printf("Invalid ceiling or floor colour\n");
		return (0);
	}
	*colour = create_trgb(0, R, G, B);
	ft_free_array(str);
	return (1);
}
