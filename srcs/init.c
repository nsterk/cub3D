/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:11:35 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/26 16:49:02 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_ray(t_ray *ray)
{
	ray->time = 0;
	ray->old_time = 0;
}

static void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}

void	init_data(t_data *data)
{
	init_ray(&data->ray);
	init_keys(&data->keys);
	data->file.line = NULL;
	data->map.spawn_char = '@';
	data->move_speed = 0.15;
	data->rot_speed = 0.05;
}

void	complete_data(t_data *data)
{
	complete_tex(data);
	data->pos = data->map.spawn_pos;
	data->dir = data->map.spawn_dir;
	data->plane = data->map.plane;
}

void	complete_tex(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		data->tex[i].img.img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->tex[i].path, &data->tex[i].width, &data->tex[i].height);
		data->tex[i].img.addr = mlx_get_data_addr(data->tex[i].img.img_ptr,
			&data->tex[i].img.bits_pp, &data->tex[i].img.len,
			&data->tex[i].img.endian);
		i++;
	}
}