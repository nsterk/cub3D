/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_alloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/13 18:12:11 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/27 18:52:15 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	free_str_array(char **str, int len)
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

void	free_int_array(int **arr, int len)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (i < len)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	close_free(t_data *data)
{
	if (data->status >= READ_ERROR)
	{
		free_parse(data);
		if (data->ray.z_buffer)
			free(data->ray.z_buffer);
		if (data->spr.pos)
			free(data->spr.pos);
		if (data->spr.distance)
			free(data->spr.distance);
	}
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
