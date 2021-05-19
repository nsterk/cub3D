/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 20:01:20 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/19 04:06:50 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	ready_for_map(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img.path == NULL)
			return (0);
		i++;
	}
	if (data->spr.img.path == NULL)
		return (0);
	if (data->res.x < 0 || data->res.y < 0)
		return (0);
	if (data->floor < 0 || data->ceiling < 0)
		return (0);
	return (1);
}

int	str_array_size(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int	validate_res(t_data *data, char *line)
{
	int	screen_x;
	int	screen_y;

	mlx_get_screen_size(data->mlx, &screen_x, &screen_y);
	if (data->res.x < 1 || data->res.y < 1)
		return (set_status(&data->status, CONFIG_ERROR));
	if (!data->file.BMP && data->res.x > screen_x || data->res.y > screen_y)
		data->res = (t_i2vec){screen_x, screen_y};
	return (1);
}
