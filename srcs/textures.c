/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 16:17:39 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/12 18:25:25 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void		init_texture(t_data *data)
{
	
}

void		calc_texture(t_data *data, t_ray *ray)
{
	if (!ray->side)
		ray->wall_x = data->pos.y + ray->perp_dist * ray->dir.y;
	else
		ray->wall_x = data->pos.x + ray->perp_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.x = (int)(ray->wall_x * (double)data->tex_width);
	if (!ray->side && ray->dir.x > 0)
		ray->tex.x = data->tex_width - ray->tex.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.x = data->tex_width - ray->tex.x - 1;
}

void		put_texture(t_data *data, t_ray *ray)
{
	t_colour	colour;
	int			y;

	y = ray->line_start;
	while (y < ray->line_end)
	{

	}
}
