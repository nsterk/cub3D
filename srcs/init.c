/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:11:35 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/09 18:12:12 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_file(t_file *file)
{
	file->line = NULL;
	file->res.x = 0;
	file->res.y = 0;
	file->tex_north = NULL;
	file->tex_south = NULL;
	file->tex_west = NULL;
	file->tex_east = NULL;
	file->tex_sprite = NULL;
	file->floor.R = 0;
	file->floor.G = 0;
	file->floor.B = 0;
	file->ceiling.R = 0;
	file->ceiling.G = 0;
	file->ceiling.B = 0;
}

void	init_data(t_data *data)
{
	init_file(&data->file);
	data->res.y = 400;
	data->res.x = 400;
	data->pos.x = 2;
	data->pos.y = 2;
	data->dir.x = -1;
	data->dir.y = 0;
	data->plane.x = 0;
	data->plane.y = 0.66;
	data->time = 0;
	data->old_time = 0;
	data->map_size = 64;
	data->map_x = 8;
	data->map_y = 8;
}
