/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_alloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 18:12:11 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/13 19:42:52 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	free_alloc(void **data, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

void	close_free(t_data *data)
{
	if (data->status != SUCCESS && data->status != BMP_ERROR)
		free_parse(data);
	if (data->file.fd != -1)
		close(data->file.fd);
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
			free(data->tex[i].img.path);
		i++;
	}
	if (data->spr.img.path)
		free(data->spr.img.path);
	if (data->file.fd != -1)
		close(data->file.fd);
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
