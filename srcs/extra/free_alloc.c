/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_alloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 18:12:11 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/19 04:04:36 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	free_alloc(char **str, int len)
{
	int	i;

	i = 0;
	if (str)
	{
		while (i < len)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	close_free(t_data *data)
{
	if (data->status != SUCCESS)
		free_parse(data);
	if (data->ray.z_buffer)
		free(data->ray.z_buffer);
	if (data->spr.pos)
		free(data->spr.pos);
	if (data->spr.distance)
		free(data->spr.distance);
}

void	free_parse(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img.path)
		{
			free(data->tex[i].img.path);
			data->tex[i].img.path = NULL;
		}
		i++;
	}
	if (data->spr.img.path)
		free(data->spr.img.path);
	data->spr.img.path = NULL;
}

void	free_map(t_map *map, int len)
{
	int	i;

	i = 0;
	if (len == 0)
		len = map->y;
	while (i < len)
	{
		free(map->check[i]);
		i++;
	}
	free(map->check);
}
