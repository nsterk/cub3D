/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 16:17:39 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/16 20:55:45 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	calc_texture(t_data *data)
{
	t_ray	*ray;
	t_tex	*tex;

	ray = &data->ray;
	tex = &data->tex[0];
	if (!ray->side)
		tex->wall_x = data->pos.y + ray->perp_dist * ray->dir.y;
	else
		tex->wall_x = data->pos.x + ray->perp_dist * ray->dir.x;
	tex->wall_x -= floor(tex->wall_x);
	tex->x = (int)(tex->wall_x * (double)tex->width);
	if (!ray->side && ray->dir.x > 0)
		tex->x = tex->width - tex->x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		tex->x = tex->width - tex->x - 1;
}

void	put_texture(t_data *data, int x)
{
	t_ray	*ray;
	t_tex	*tex;
	int		colour;
	int		y;

	ray = &data->ray;
	tex = &data->tex[0];
	calc_texture(data);
	y = ray->line_start;
	tex->step = 1.0 * tex->height / ray->line_height;
	tex->pos = (ray->line_start - data->res.y / 2
		+ ray->line_height / 2) * tex->step;
	while (y < ray->line_end)
	{
		tex->y = (int)(tex->pos) & (tex->height - 1);
		tex->pos += tex->step;
		colour = get_colour(tex);
		if (ray->side == 1)
			colour = (colour >> 1) & 8355711;
		put_pixel(x, y, colour, &data->img);
		y++;
	}
}

int		get_colour(t_tex *tex)
{
	int	colour;
	
	colour = *(int*) (tex->img.addr + (tex->y * tex->img.len
		+ tex->x * (tex->img.bits_pp / 8)));
	return (colour);
}