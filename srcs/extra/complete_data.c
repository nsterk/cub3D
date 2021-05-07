/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 19:14:28 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/06 18:02:06 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	complete_data(t_data *data)
{
	complete_tex(data);
	data->pos = data->map.spawn_pos;
	data->dir = data->map.spawn_dir;
	data->plane = data->map.plane;
	data->sprites.amount = data->map.nr_sprites;
	data->ray.z_buffer = malloc(sizeof(*(data->ray.z_buffer)) * data->res.x);
	if (!data->ray.z_buffer)
		return (0);
	if (!alloc_sprite(&data->sprites))
		return (0);
	complete_sprites(data->map.grid, data->sprites.pos, data->map.x,
		data->map.y);
	return (1);
}

void	complete_tex(t_data *data)
{
	int			i;
	t_tex		*tex;
	t_sprite	*spr;

	i = 0;
	while (i < 4)
	{
		tex = &data->tex[i];
		tex->img.ptr = mlx_xpm_file_to_image(data->mlx, tex->path,
				&tex->img.width, &tex->img.height);
		tex->img.addr = mlx_get_data_addr(tex->img.ptr, &tex->img.bpp,
				&tex->img.len, &tex->img.endian);
		i++;
	}
	spr = &data->sprites;
	spr->img.ptr = mlx_xpm_file_to_image(data->mlx,
			spr->path, &spr->img.width, &spr->img.height);
	spr->img.addr = mlx_get_data_addr(spr->img.ptr,
			&spr->img.bpp, &spr->img.len, &spr->img.endian);
}

int		alloc_sprite(t_sprite *sprites)
{
	sprites->pos = malloc(sizeof(t_d2vec) * sprites->amount);
	if (!sprites->pos)
		return (0);
	sprites->distance = malloc(sizeof(double) * sprites->amount);
	if (!sprites->distance)
		return (0);
	return (1);
}

void	complete_sprites(char **map, t_d2vec *pos, int *xmax, int ymax)
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