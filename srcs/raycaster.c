/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 12:53:51 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/03 08:27:56 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>
#include <stdio.h>

void	raycaster(t_data *data)
{
	int		x;
	int		colour;
	t_ray	ray;

	x = 0;
	while (x < data->res.x)
	{
		ray.camera_x = 2 * x / (double)data->res.x - 1;
		ray.dir.x = data->dir.x + data->plane.x * ray.camera_x;
		ray.dir.y = data->dir.y + data->plane.y * ray.camera_x;
		ray.map.x = (int)data->pos.x;
		ray.map.y = (int)data->pos.y;
		ray.delta_dist.x = fabs(1 / ray.dir.x);
		ray.delta_dist.y = fabs(1 / ray.dir.y);
		ray.hit = 0;
		calc_step_distance(data, &ray);
		differential_analysis(data, &ray);
		ray.line_height = (int)(data->res.x / ray.perp_dist);
		ray.line_start = -ray.line_height / 2 + data->res.x / 2;
		if (ray.line_start < 0)
			ray.line_start = 0;
		ray.line_end = ray.line_height / 2 + data->res.x / 2;
		if (ray.line_end >= data->res.x)
			ray.line_end = data->res.x - 1;
	}
	colour = RED;
	if (ray.side == 1)
		colour /= 2;
	put_line(x, ray.line_start, ray.line_end, colour, &data->img);
	x++;
}

void	calc_step_distance(t_data *data, t_ray *ray)
{
	/* calculate step and side_dist X */
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (data->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - data->pos.x) * ray->delta_dist.x;
	}
	/* calculate step and side_dist Y */
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (data->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - data->pos.y) * ray->delta_dist.y;
	}
}

void	differential_analysis(t_data *data, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (data->map[ray->map.y][ray->map.x] == '1')
			ray->hit = 1;
	}
}
