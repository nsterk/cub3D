/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 19:14:28 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/24 13:44:47 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <fcntl.h>

int	complete_data(t_data *data)
{
	int	i;

	if (!start_mlx(data))
		return (set_status(&data->status, IMG_ERROR));
	data->mlx_status = 1;
	i = 0;
	while (i < 4)
	{
		if (!complete_img(&data->status, &data->tex[i].img, data->mlx))
			return (0);
		i++;
	}
	if (!complete_img(&data->status, &data->spr.img, data->mlx))
		return (0);
	complete_sprites(&data->status, &data->spr, &data->map);
	data->ray.z_buffer = malloc(sizeof(*(data->ray.z_buffer)) * data->res.x);
	if (!data->ray.z_buffer)
		return (set_status(&data->status, MALLOC_ERROR));
	free_parse(data);
	return (1);
}

int	complete_img(t_status *status, t_img *img, void *mlx)
{
	size_t		len;

	len = ft_strlen(img->path);
	if (!check_validity_path(img->path))
		return (set_status(status, CONFIG_ERROR));
	if (!ft_strcmp(img->path + (len - 4), ".xpm"))
		img->ptr = mlx_xpm_file_to_image(mlx, \
		img->path, &img->width, &img->height);
	else if (!ft_strcmp(img->path + (len - 4), ".png"))
		img->ptr = mlx_png_file_to_image(mlx, \
		img->path, &img->width, &img->height);
	else
		return (set_status(status, CONFIG_ERROR));
	if (!img->ptr)
		return (set_status(status, IMG_ERROR));
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->len, &img->endian);
	if (!img->addr)
		return (set_status(status, IMG_ERROR));
	return (1);
}

int	complete_sprites(t_status *status, t_sprite *spr, t_map *map)
{
	spr->pos = malloc(sizeof(t_d2vec) * spr->amount);
	spr->distance = malloc(sizeof(double) * spr->amount);
	if (!spr->pos || !spr->distance)
		return (set_status(status, MALLOC_ERROR));
	position_sprites(map->grid, spr->pos, map->x, map->y);
	return (1);
}

void	position_sprites(char **map, t_d2vec *pos, int *xmax, int ymax)
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

int	check_validity_path(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
