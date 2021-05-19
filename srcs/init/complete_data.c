/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 19:14:28 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/19 17:29:12 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	complete_data(t_data *data)
{
	int	i;

	start_mlx(data);
	i = 0;
	while (i < 4)
	{
		complete_img(&data->status, &data->tex[i].img, data->mlx);
		i++;
	}
	complete_img(&data->status, &data->spr.img, data->mlx);
	if (!complete_sprites(data))
		return (0);
	data->pos = data->map.spawn_pos;
	data->dir = data->map.spawn_dir;
	data->plane = data->map.plane;
	data->ray.z_buffer = malloc(sizeof(*(data->ray.z_buffer)) * data->res.x);
	if (!data->ray.z_buffer)
		return (set_status(&data->status, MALLOC_ERROR));
	free_parse(data);
	return (1);
}

int	complete_img(t_status *status, t_img *img, void *mlx)
{
	int			i;
	size_t		len;

	len = ft_strlen(img->path);
	if (!ft_strcmp(img->path + (len - 4), ".xpm"))
		img->ptr = mlx_xpm_file_to_image(mlx, \
		img->path, &img->width, &img->height);
	else
		img->ptr = mlx_png_file_to_image(mlx, \
		img->path, &img->width, &img->height);
	if (!img->ptr)
		return (set_status(status, IMG_ERROR));
	img->addr = mlx_get_data_addr(img->ptr, \
	&img->bpp, &img->len, &img->endian);
	return (1);
}

// int	complete_tex(t_status *status, t_tex *tex, void *mlx)
// {
// 	int			i;
// 	size_t		len;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		len = ft_strlen(data->tex[i].img.path);
// 		if (ft_strcmp(data)data->tex[i].img.path[len - 1] == 'm')
// 			data->tex[i].img.ptr = mlx_xpm_file_to_image(data->mlx, \
// 			data->tex[i].img.path, &data->tex[i].img.width, \
// 			&data->tex[i].img.height);
// 		else
// 			data->tex[i].img.ptr = mlx_png_file_to_image(data->mlx, \
// 			data->tex[i].img.path, &data->tex[i].img.width, \
// 			&data->tex[i].img.height);
// 		if (!data->tex[i].img.ptr)
// 			return (set_status(&data->status, IMG_ERROR));
// 		data->tex[i].img.addr = mlx_get_data_addr(data->tex[i].img.ptr, \
// 		&data->tex[i].img.bpp, &data->tex[i].img.len, &data->tex[i].img.endian);
// 		i++;
// 	}
// 	return (1);
// }
