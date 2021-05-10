/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 19:14:28 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/10 18:38:59 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	complete_data(t_data *data)
{
	complete_tex(data);
	complete_sprites(data);
	data->pos = data->map.spawn_pos;
	data->dir = data->map.spawn_dir;
	data->plane = data->map.plane;
	data->ray.z_buffer = malloc(sizeof(*(data->ray.z_buffer)) * data->res.x);
	if (!data->ray.z_buffer)
		return (0);
	return (1);
}

void	complete_tex(t_data *data)
{
	int			i;
	size_t		len;

	i = 0;
	while (i < 4)
	{
		len = ft_strlen(data->tex[i].path);
		if (data->tex[i].path[len - 1] == 'm')
			data->tex[i].img.ptr = mlx_xpm_file_to_image(data->mlx, data->tex[i].path, \
			&data->tex[i].img.width, &data->tex[i].img.height);
		else
			data->tex[i].img.ptr = mlx_png_file_to_image(data->mlx, data->tex[i].path, \
			&data->tex[i].img.width, &data->tex[i].img.height);
		data->tex[i].img.addr = mlx_get_data_addr(data->tex[i].img.ptr, &data->tex[i].img.bpp, \
		&data->tex[i].img.len, &data->tex[i].img.endian);
		i++;
	}
}
