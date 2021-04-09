/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 12:53:51 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/09 20:01:53 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>
#include <stdio.h>

void	calc_line(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map.x - data->pos.x + \
		(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_dist = (ray->map.y - data->pos.y + \
		(1 - ray->step.y) / 2) / ray->dir.y;
	ray->line_height = (int)(data->res.y / ray->perp_dist);
	if (ray->line_height < 0)
		ray->line_height = data->res.y - 1;
	ray->line_start = -ray->line_height / 2 + data->res.y / 2;
	if (ray->line_start < 0)
		ray->line_start = 0;
	ray->line_end = ray->line_height / 2 + data->res.y / 2;
	if (ray->line_end >= data->res.y)
		ray->line_end = data->res.y - 1;
}

void	raycaster(t_data *data, int x)
{
	int		colour;
	t_ray	ray;

	ray.camera_x = 2 * x / (double)data->res.x - 1;
	ray.dir.x = data->dir.x + data->plane.x * ray.camera_x;
	ray.dir.y = data->dir.y + data->plane.y * ray.camera_x;
	ray.map.x = data->pos.x;
	ray.map.y = data->pos.y;
	ray.delta_dist.x = fabs(1 / ray.dir.x);
	ray.delta_dist.y = fabs(1 / ray.dir.y);
	/*
	if (ray.dir.y == 0)
		ray.delta_dist.x = 0;
	else if (ray.dir.x == 0)
		ray.delta_dist.x = 1;
	else
		ray.delta_dist.x = fabs(1 / ray.dir.x);
	if (ray.dir.x == 0)
		ray.delta_dist.y = 0;
	else if (ray.dir.y == 0)
		ray.delta_dist.y = 1;
	else
		ray.delta_dist.y = fabs(1 / ray.dir.y);
		*/
	calc_step_distance(data, &ray);
	differential_analysis(data, &ray);
	calc_line(data, &ray);
	colour = LIGHTGRAY;
	if (ray.side == 1)
		colour = DARKGRAY;
	/*
	if (x == 150)
	{
		printf("camera_x: %f\nmap x ,y: %i, %i\n", ray.camera_x, ray.map.x, ray.map.y);
		printf("dir x,y: %f, %f\n", ray.dir.x, ray.dir.y);
		printf("side_dist x,y: %f, %f\n", ray.side_dist.x, ray.side_dist.y);
		printf("delta_dist x,y: %f, %f\n", ray.delta_dist.x, ray.delta_dist.y);
		printf("step x,y: %i, %i\n", ray.step.x, ray.step.y);
		printf("perp_dist: %f\nside: %i\nline_height: %i\nline_start: %i\nline_end: %i\n", ray.perp_dist, ray.side, ray.line_height, ray.line_start, ray.line_end);
	}
	*/
	put_line(x, ray.line_start, ray.line_end, colour, &data->img);
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
	while (1)
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
			break ;
	}
}
