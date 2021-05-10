/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/05 16:03:29 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/10 18:04:06 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <math.h>

int	draw_sprites(t_data *data)
{
	int	i;

	i = 0;
	fill_distances(data->pos, &data->spr);
	sort_sprites(&data->spr);
	while (i < data->spr.amount)
	{
		calculate_sprite(data, i);
		put_sprite(data);
		i++;
	}
	return (0);
}	

void	fill_distances(t_d2vec pos, t_sprite *spr)
{
	int	i;

	i = 0;
	while (i < spr->amount)
	{
		spr->distance[i] = ((pos.x - spr->pos[i].x)
				* (pos.x - spr->pos[i].x)) + ((pos.y - spr->pos[i].y)
				* (pos.y - spr->pos[i].y));
		i++;
	}
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
	t_sprite	*spr;

	spr = &data->spr;
	spr->cam.x = spr->pos[i].x - data->pos.x;
	spr->cam.y = spr->pos[i].y - data->pos.y;
	spr->inv = 1.0 / ((data->plane.x * data->dir.y)
			- (data->dir.x * data->plane.y));
	spr->transform.x = spr->inv * ((data->dir.y * spr->cam.x)
			- (data->dir.x * spr->cam.y));
	spr->transform.y = spr->inv * ((-data->plane.y * spr->cam.x)
			+ (data->plane.x * spr->cam.y));
	spr->screen_x = (int)((data->res.x / 2) * (1
				+ (spr->transform.x / spr->transform.y)));
	spr->height = abs((int)(1 * (data->res.y / spr->transform.y)));
	spr->start.y = (-spr->height / 2) + (data->res.y / 2);
	if (spr->start.y < 0)
		spr->start.y = 0;
	spr->end.y = (spr->height / 2) + (data->res.y / 2);
	if (spr->end.y >= data->res.y)
		spr->end.y = data->res.y - 1;
	spr->width = abs((int)(1 * (data->res.y / spr->transform.y)));
	spr->start.x = -spr->width / 2 + spr->screen_x;
	if (spr->start.x < 0)
		spr->start.x = 0;
	spr->end.x = spr->width / 2 + spr->screen_x;
	if (spr->end.x >= data->res.x)
		spr->end.x = data->res.x - 1;
}

void	put_sprite(t_data *data)
{
	t_sprite	*spr;
	int			y;

	spr = &data->spr;
	spr->stripe = spr->start.x;
	while (spr->stripe < spr->end.x)
	{
		spr->tex.x = (int)(256 * (spr->stripe - (-spr->width / 2
						+ spr->screen_x)) * spr->img.width / spr->width) / 256;
		y = spr->start.y;
		if (spr->transform.y > 0 && spr->stripe > 0 && spr->stripe < data->res.x
			&& spr->transform.y < data->ray.z_buffer[spr->stripe])
		{
			while (y < spr->end.y)
			{
				put_pixel_sprite(data, y);
				y++;
			}
		}
		spr->stripe++;
	}
}

void	put_pixel_sprite(t_data *data, int y)
{
	int			d;
	int			colour;
	t_sprite	*spr;

	spr = &data->spr;
	d = (y * 256) - (data->res.y * 128) + (spr->height * 128);
	spr->tex.y = (d * spr->img.height) / spr->height / 256;
	colour = *(int *)(spr->img.addr + (spr->tex.y * spr->img.len
				+ spr->tex.x * (spr->img.bpp / 8)));
	if (colour > 0)
	{
		*(int *)(data->img.addr + (y * data->img.len) + (spr->stripe
					* (data->img.bpp / 8))) = colour;
	}
}
