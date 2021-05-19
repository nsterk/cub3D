/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_02.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 20:28:47 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/19 20:34:15 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}

void	init_mlx(t_img *img, void *mlx, void *window)
{
	mlx = NULL;
	window = NULL;
	init_img(img);
}

void	init_file(t_file *file)
{
	file->line = NULL;
	file->ret = 1;
}

void	init_unsorted(t_data *data)
{
	data->ceiling = 0;
	data->floor = 0;
	data->res = (t_i2vec){0, 0};
	data->status = SUCCESS;
	data->ray.z_buffer = NULL;
	data->map.spawn_char = '@';
	data->move_speed = 0.15;
	data->rot_speed = 0.05;
}