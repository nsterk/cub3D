/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:11:35 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/10 18:12:32 by nsterk        ########   odam.nl         */
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
	data->spr.path = NULL;
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