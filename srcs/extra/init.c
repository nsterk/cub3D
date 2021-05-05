/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:11:35 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/05 14:40:23 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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
	size_t	i;

	init_keys(&data->keys);
	data->file.line = NULL;
	data->sprite.path = NULL;
	data->map.nr_sprites = 0;
	data->map.spawn_char = '@';
	data->move_speed = 0.15;
	data->rot_speed = 0.05;
	i = 0;
	while (i < 4)
	{
		data->tex[i].path = NULL;
		i++;
	}
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
			&data->tex[i].img.bpp, &data->tex[i].img.len,
			&data->tex[i].img.endian);
		i++;
	}
	data->sprite.img.img_ptr =  mlx_xpm_file_to_image(data->mlx,
		data->sprite.path, &data->sprite.width, &data->sprite.height);
	data->sprite.img.addr = mlx_get_data_addr(data->sprite.img.img_ptr,
			&data->sprite.img.bpp, &data->sprite.img.len,
			&data->sprite.img.endian);
}