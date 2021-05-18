/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 16:17:39 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/18 13:37:38 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <math.h>

void	calc_texture(t_data *data, int i)
{
	t_ray	*ray;
	t_tex	*tex;

	ray = &data->ray;
	tex = &data->tex[i];
	if (!ray->side)
		tex->wall_x = data->pos.y + ray->perp_dist * ray->dir.y;
	else
		tex->wall_x = data->pos.x + ray->perp_dist * ray->dir.x;
	tex->wall_x -= floor(tex->wall_x);
	tex->x = (int)(tex->wall_x * (double)tex->img.width);
	if (!ray->side && ray->dir.x > 0)
		tex->x = tex->img.width - tex->x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		tex->x = tex->img.width - tex->x - 1;
}

void	put_texture(t_data *data, int x, int i)
{
	int		colour;
	int		y;

	calc_texture(data, i);
	y = data->ray.line_start;
	data->tex[i].step = 1.0 * data->tex[i].img.height / data->ray.line_height;
	data->tex[i].pos = (data->ray.line_start - data->res.y / 2 \
		+ data->ray.line_height / 2) * data->tex[i].step;
	while (y < data->ray.line_end)
	{
		data->tex[i].y = (int)(data->tex[i].pos) & \
			(data->tex[i].img.height - 1);
		data->tex[i].pos += data->tex[i].step;
		colour = *(int *)(data->tex[i].img.addr + \
			(data->tex[i].y * data->tex[i].img.len + \
			data->tex[i].x * (data->tex[i].img.bpp / 8)));
		if (data->ray.side == 1)
			colour = (colour >> 1) & 8355711;
		put_pixel(x, y, colour, &data->img);
		y++;
	}
}
