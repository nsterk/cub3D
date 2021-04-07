/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 14:28:37 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/07 14:41:14 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_up(t_data *data)
{
	if (data->map[(int)data->pos.y][(int)(data->pos.x + data->dir.x * data->move_speed)] != '1')
		data->pos.x += data->dir.x * data->move_speed;
	if (data->map[(int)(data->pos.y + data->dir.y * data->move_speed)][(int)data->pos.x] != '1')
		data->pos.y += data->dir.y * data->move_speed;
}

void	move_down(t_data *data)
{
	if (data->map[(int)data->pos.y][(int)(data->pos.x - data->dir.x * data->move_speed)] != '1')
		data->pos.x -= data->dir.x * data->move_speed;
	if (data->map[(int)(data->pos.y - data->dir.y * data->move_speed)][(int)data->pos.x] != '1')
		data->pos.y -= data->dir.y * data->move_speed;
}

void	move_left(t_data *data)
{
	if (data->map[(int)data->pos.y][(int)(data->pos.x - data->plane.x * data->move_speed)] != '1')
		data->pos.x -= data->plane.x * data->move_speed;
	if (data->map[(int)(data->pos.y - data->plane.y * data->move_speed)][(int)data->pos.x] != '1')
		data->pos.y -= data->plane.y * data->move_speed;
}
void	move_right(t_data *data)
{
	if (data->map[(int)data->pos.y][(int)(data->pos.x + data->plane.x * data->move_speed)] != '1')
		data->pos.x += data->plane.x * data->move_speed;
	if (data->map[(int)(data->pos.y + data->plane.y * data->move_speed)][(int)data->pos.x] != '1')
		data->pos.y += data->plane.y * data->move_speed;
}
