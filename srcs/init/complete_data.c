/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 19:14:28 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/10 18:12:16 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	complete_data(t_data *data)
{
	complete_tex(data);
	data->pos = data->map.spawn_pos;
	data->dir = data->map.spawn_dir;
	data->plane = data->map.plane;
	data->spr.amount = data->map.nr_sprites;
	data->ray.z_buffer = malloc(sizeof(*(data->ray.z_buffer)) * data->res.x);
	if (!data->ray.z_buffer)
		return (0);
	complete_sprites(data);
	return (1);
}

void	complete_tex(t_data *data)
{
	int			i;
	size_t		len;
	t_tex		*tex;

	i = 0;
	while (i < 4)
	{
		tex = &data->tex[i];
		len = ft_strlen(tex->path);
		if (tex->path[len - 1] == 'm')
			tex->img.ptr = mlx_xpm_file_to_image(data->mlx, tex->path,
					&tex->img.width, &tex->img.height);
		else
			tex->img.ptr = mlx_png_file_to_image(data->mlx, tex->path,
					&tex->img.width, &tex->img.height);
		tex->img.addr = mlx_get_data_addr(tex->img.ptr, &tex->img.bpp,
				&tex->img.len, &tex->img.endian);
		i++;
	}
}
