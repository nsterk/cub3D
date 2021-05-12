/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_sprites.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 17:54:52 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/12 04:51:39 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	complete_sprites(t_data *data)
{
	size_t		len;

	data->spr.amount = data->map.nr_sprites;
	if (!alloc_sprite(&data->spr))
		return (set_status(&data->status, MALLOC_ERROR));
	len = ft_strlen(data->spr.img.path);
	if (data->spr.img.path[len - 1] == 'm')
		data->spr.img.ptr = mlx_xpm_file_to_image(data->mlx, data->spr.img.path, \
		&data->spr.img.width, &data->spr.img.height);
	else
		data->spr.img.ptr = mlx_png_file_to_image(data->mlx, data->spr.img.path, \
		&data->spr.img.width, &data->spr.img.height);
	if (data->spr.img.ptr)
		return (set_status(&data->status, IMG_ERROR));
	data->spr.img.addr = mlx_get_data_addr(data->spr.img.ptr, &data->spr.img.bpp, \
	&data->spr.img.len, &data->spr.img.endian);
	pos_sprites(data->map.grid, data->spr.pos, data->map.x, data->map.y);
	return (1);
}

int	alloc_sprite(t_sprite *sprites)
{
	sprites->pos = malloc(sizeof(t_d2vec) * sprites->amount);
	if (!sprites->pos)
		return (0);
	sprites->distance = malloc(sizeof(double) * sprites->amount);
	if (!sprites->distance)
		return (0);
	return (1);
}

void	pos_sprites(char **map, t_d2vec *pos, int *xmax, int ymax)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (y < ymax)
	{
		x = 0;
		while (x < xmax[y])
		{
			if (map[y][x] == '2')
			{
				pos[i] = (t_d2vec){x + 0.5, y + 0.5};
				i++;
			}
			x++;
		}
		y++;
	}
}
