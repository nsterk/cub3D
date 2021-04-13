/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:11:35 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/13 16:04:40 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_file(t_file *file)
{
	file->line = NULL;
	file->map = NULL;
	file->map_check = NULL;
	file->res = (t_i2vec){0,0};
	file->spawn = (t_i2vec){9, 6};
	file->tex_north = NULL;
	file->tex_south = NULL;
	file->tex_west = NULL;
	file->tex_east = NULL;
	file->tex_sprite = NULL;
	file->floor = (t_colour){-1, -1, -1};
	file->ceiling = (t_colour){-1, -1, -1};

}

void	complete_data(t_data *data)
{
	data->ceiling = create_trgb(0, data->file.ceiling.R,
		data->file.ceiling.G, data->file.ceiling.B);
	data->floor = create_trgb(0, data->file.floor.R,
		data->file.floor.G, data->file.floor.B);
}

void	init_data(t_data *data)
{
	init_file(&data->file);
	data->res = (t_i2vec){400, 400};
	data->pos = (t_d2vec){9, 6};
	data->dir = (t_d2vec){-1, 0};
	data->plane = (t_d2vec){0.0, 0.66};
	data->move_speed = 0.15;
	data->rot_speed = 0.05;
	data->time = 0;
	data->old_time = 0;
	data->tex_width = 64;
	data->tex_height = 64;
}
