/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 19:14:28 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/06 12:27:41 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	complete_data(t_data *data)
{
	int	i;
	i = 0;
	complete_tex(data);
	data->pos = data->map.spawn_pos;
	data->dir = data->map.spawn_dir;
	data->plane = data->map.plane;
	data->sprites.amount = data->map.nr_sprites;
	data->ray.z_buffer = malloc(sizeof(*(data->ray.z_buffer)) * data->res.x);
	if (!data->ray.z_buffer)
		return (0);
	data->sprites.pos = malloc(sizeof(t_d2vec) * data->sprites.amount);
	if (!data->sprites.pos)
		return (0);
	complete_sprites(data->map.grid, data->sprites.pos, data->map.x, data->map.y);
	return (1);
}

void	complete_tex(t_data *data)
{
	int	i;

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
	data->sprites.img.img_ptr =  mlx_xpm_file_to_image(data->mlx,
		data->sprites.path, &data->sprites.width, &data->sprites.height);
	data->sprites.img.addr = mlx_get_data_addr(data->sprites.img.img_ptr,
			&data->sprites.img.bpp, &data->sprites.img.len,
			&data->sprites.img.endian);
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