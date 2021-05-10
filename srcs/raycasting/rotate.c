/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 15:38:53 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/10 18:50:20 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <math.h>

void	rotate_right(t_data *data)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->dir.x;
	old_planex = data->plane.x;
	data->dir.x = data->dir.x * cos(data->rot_speed) - data->dir.y * \
		sin(data->rot_speed);
	data->dir.y = old_dirx * sin(data->rot_speed) + data->dir.y * \
		cos(data->rot_speed);
	data->plane.x = data->plane.x * cos(data->rot_speed) \
		- data->plane.y * sin(data->rot_speed);
	data->plane.y = old_planex * sin(data->rot_speed) \
		+ data->plane.y * cos(data->rot_speed);
}

void	rotate_left(t_data *data)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->dir.x;
	old_planex = data->plane.x;
	data->dir.x = data->dir.x * cos(-data->rot_speed) - \
		data->dir.y * sin(-data->rot_speed);
	data->dir.y = old_dirx * sin(-data->rot_speed) + \
		data->dir.y * cos(-data->rot_speed);
	data->plane.x = data->plane.x * cos(-data->rot_speed) - \
		data->plane.y * sin(-data->rot_speed);
	data->plane.y = old_planex * sin(-data->rot_speed) + \
		data->plane.y * cos(-data->rot_speed);
}
