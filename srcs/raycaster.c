/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 12:53:51 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/16 14:22:08 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	calc_line(t_d2vec pos, t_i2vec res, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map.x - pos.x + \
		(1.0 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_dist = (ray->map.y - pos.y + \
		(1.0 - ray->step.y) / 2) / ray->dir.y;
	ray->line_height = (int)(res.y / ray->perp_dist);
	if (ray->line_height < 0)
		ray->line_height = res.y - 1;
	ray->line_start = -ray->line_height / 2 + res.y / 2;
	if (ray->line_start < 0)
		ray->line_start = 0;
	ray->line_end = ray->line_height / 2 + res.y / 2;
	if (ray->line_end >= res.y)
		ray->line_end = res.y - 1;
}

void	raycaster(t_data *data, int x)
{
	int		colour;
	t_ray	*ray;

	ray = &data->ray;
	ray->camera_x = 2 * x / (double)data->res.x - 1;
	ray->dir.x = data->dir.x + data->plane.x * ray->camera_x;
	ray->dir.y = data->dir.y + data->plane.y * ray->camera_x;
	ray->map.x = (int)data->pos.x;
	ray->map.y = (int)data->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	calc_step_distance(data->pos, ray);
	differential_analysis(data);
	calc_line(data->pos, data->res, ray);
	colour = LIGHTGRAY;
	if (ray->side == 1)
		colour = DARKGRAY;
	put_line(x, *ray, colour, &data->img);
}

void	calc_step_distance(t_d2vec pos, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - pos.y) * ray->delta_dist.y;
	}
}

void	differential_analysis(t_data *data)
{
	while (1)
	{
		if (data->ray.side_dist.x < data->ray.side_dist.y)
		{
			data->ray.side_dist.x += data->ray.delta_dist.x;
			data->ray.map.x += data->ray.step.x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist.y += data->ray.delta_dist.y;
			data->ray.map.y += data->ray.step.y;
			data->ray.side = 1;
		}
		if (data->map.grid[data->ray.map.y][data->ray.map.x] == '1')
			break ;
	}
}
