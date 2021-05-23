/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/23 16:30:33 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/23 16:44:58 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <math.h>

int	draw_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->spr.amount)
	{
		data->spr.distance[i] = ((data->pos.x - data->spr.pos[i].x) * \
			(data->pos.x - data->spr.pos[i].x)) + ((data->pos.y - \
			data->spr.pos[i].y) * (data->pos.y - data->spr.pos[i].y));
		i++;
	}
	i = 0;
	sort_sprites(&data->spr);
	while (i < data->spr.amount)
	{
		calculate_sprite(data, i);
		put_sprite(&data->spr, data->res, data->ray.z_buffer, &data->img);
		i++;
	}
	return (0);
}

void	sort_sprites(t_sprite *spr)
{
	int		i;
	int		swapped;
	t_d2vec	tmp_pos;
	double	tmp_dist;

	i = 0;
	while (i < (spr->amount - 1))
	{
		swapped = 0;
		if (spr->distance[i + 1] > spr->distance[i])
		{
			tmp_pos = (t_d2vec)spr->pos[i];
			tmp_dist = spr->distance[i];
			spr->pos[i] = (t_d2vec)spr->pos[i + 1];
			spr->distance[i] = spr->distance[i + 1];
			spr->pos[i + 1] = (t_d2vec)tmp_pos;
			spr->distance[i + 1] = tmp_dist;
			swapped++;
		}
		if (swapped)
			i = 0;
		else
			i++;
	}
}

void	calculate_sprite(t_data *data, int i)
{
	data->spr.cam.x = data->spr.pos[i].x - data->pos.x;
	data->spr.cam.y = data->spr.pos[i].y - data->pos.y;
	data->spr.inv = 1.0 / ((data->plane.x * data->dir.y) - \
		(data->dir.x * data->plane.y));
	data->spr.transform.x = data->spr.inv * ((data->dir.y * data->spr.cam.x) - \
		(data->dir.x * data->spr.cam.y));
	data->spr.transform.y = data->spr.inv * ((-data->plane.y * data->spr.cam.x) \
	+ (data->plane.x * data->spr.cam.y));
	data->spr.screen_x = (int)((data->res.x / 2) * (1 + \
		(data->spr.transform.x / data->spr.transform.y)));
	data->spr.height = abs((int)(1 * (data->res.y / data->spr.transform.y)));
	data->spr.start.y = (-data->spr.height / 2) + (data->res.y / 2);
	if (data->spr.start.y < 0)
		data->spr.start.y = 0;
	data->spr.end.y = (data->spr.height / 2) + (data->res.y / 2);
	if (data->spr.end.y >= data->res.y)
		data->spr.end.y = data->res.y - 1;
	data->spr.width = abs((int)(1 * (data->res.y / data->spr.transform.y)));
	data->spr.start.x = -data->spr.width / 2 + data->spr.screen_x;
	if (data->spr.start.x < 0)
		data->spr.start.x = 0;
	data->spr.end.x = data->spr.width / 2 + data->spr.screen_x;
	if (data->spr.end.x >= data->res.x)
		data->spr.end.x = data->res.x - 1;
}

void	put_sprite(t_sprite *spr, t_i2vec res, double *z_buf, t_img *img)
{
	int			y;

	spr->stripe = spr->start.x;
	while (spr->stripe < spr->end.x)
	{
		spr->tex.x = (int)(256 * (spr->stripe - (-spr->width / 2 \
			+ spr->screen_x)) * spr->img.width / spr->width) / 256;
		y = spr->start.y;
		if (spr->transform.y > 0 && spr->stripe > 0 && spr->stripe < res.x \
			&& spr->transform.y < z_buf[spr->stripe])
		{
			while (y < spr->end.y)
			{
				put_pixel_sprite(spr, res.y, img, y);
				y++;
			}
		}
		spr->stripe++;
	}
}

void	put_pixel_sprite(t_sprite *spr, int res_y, t_img *mlx_img, int y)
{
	int			d;
	t_colour	colour;

	d = (y * 256) - (res_y * 128) + (spr->height * 128);
	spr->tex.y = (d * spr->img.height) / spr->height / 256;
	colour = get_colour(spr);
	apply_shade(spr, &colour);
	if ((colour.colour & 0x00FFFFFF) != 0)
	{
		*(unsigned int *)(mlx_img->addr + (y * mlx_img->len) + (spr->stripe \
			 * (mlx_img->bpp / 8))) = colour.colour;
	}
}
