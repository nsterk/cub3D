/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:11:35 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/19 17:19:15 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_ray(t_ray *ray)
{
	ray->time = 0;
	ray->old_time = 0;
}

void	complete_data(t_data *data)
{
	data->pos = data->map.spawn_pos;
	data->dir = data->map.spawn_dir;
	data->plane = data->map.plane;
	data->tex[0].img.img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->tex[0].path, &data->tex[0].width, &data->tex[0].height);
	data->tex[0].img.addr = mlx_get_data_addr(data->tex[0].img.img_ptr,
			&data->tex[0].img.bits_pp, &data->tex[0].img.len,
			&data->tex[0].img.endian);
}

void	init_data(t_data *data)
{
	init_ray(&data->ray);
	data->file.line = NULL;
	data->map.spawn_char = '@';
	data->move_speed = 0.15;
	data->rot_speed = 0.05;
}
