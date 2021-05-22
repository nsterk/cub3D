/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_01.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:11:35 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/20 14:58:50 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <init.h>

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		init_tex(&data->tex[i]);
		i++;
	}
	init_sprite(&data->spr);
	init_keys(&data->keys);
	init_mlx(&data->img, data->mlx, data->window);
	init_file(&data->file);
	init_map(&data->map);
	init_unsorted(data);
}

void	init_img(t_img *img)
{
	img->path = NULL;
	img->ptr = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->len = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	init_tex(t_tex *tex)
{
	init_img(&tex->img);
	tex->x = 0;
	tex->y = 0;
	tex->wall_x = 0;
	tex->step = 0;
	tex->pos = 0;
}

void	init_sprite(t_sprite *spr)
{
	init_img(&spr->img);
	spr->distance = NULL;
	spr->pos = NULL;
	spr->amount = 0;
}
