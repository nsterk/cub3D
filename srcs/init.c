/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:11:35 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/16 12:55:47 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_file(t_file *file)
{
	file->path = NULL;
	file->line = NULL;
	file->tex_north = NULL;
	file->tex_east = NULL;
	file->tex_south = NULL;
	file->tex_west = NULL;
}

static void	init_ray(t_ray *ray)
{
	
	ray->time = 0;
	ray->old_time = 0;
}

void	complete_data(t_data *data)
{
	if (data)
		return ;
}

void	init_data(t_data *data)
{
	init_file(&data->file);
	init_ray(&data->ray);
	data->res = (t_i2vec){-1, -1};
	data->plane = (t_d2vec){0.0, 0.66};
	data->pos = (t_d2vec){9, 6};
	data->dir = (t_d2vec){-1, 0};
	data->map.spawn = (t_i2vec){9, 6};
	data->map.spawn_dir = (t_d2vec){-1, 0};
	data->move_speed = 0.15;
	data->rot_speed = 0.05;
}
