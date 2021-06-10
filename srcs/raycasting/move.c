/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 14:28:37 by nsterk        #+#    #+#                 */
/*   Updated: 2021/06/06 18:41:29 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	move_hooks(t_data *data)
{
	if (data->keys.w && !data->keys.s)
		move_up(data);
	else if (data->keys.s && !data->keys.w)
		move_down(data);
	if (data->keys.a && !data->keys.d)
		move_left(data);
	else if (data->keys.d && !data->keys.a)
		move_right(data);
	if (data->keys.left && !data->keys.right)
		rotate_left(data);
	else if (data->keys.right && !data->keys.left)
		rotate_right(data);
}

void	move_up(t_data *data)
{
	if (data->map.grid[(int)data->pos.y] \
	[(int)(data->pos.x + data->dir.x * data->move_speed)] == '0')
		data->pos.x += data->dir.x * data->move_speed;
	if (data->map.grid[(int)(data->pos.y + data->dir.y * data->move_speed)] \
	[(int)data->pos.x] == '0')
		data->pos.y += data->dir.y * data->move_speed;
}

void	move_down(t_data *data)
{
	if (data->map.grid[(int)data->pos.y] \
	[(int)(data->pos.x - data->dir.x * data->move_speed)] == '0')
		data->pos.x -= data->dir.x * data->move_speed;
	if (data->map.grid[(int)(data->pos.y - data->dir.y * data->move_speed)] \
	[(int)data->pos.x] == '0')
		data->pos.y -= data->dir.y * data->move_speed;
}

void	move_left(t_data *data)
{
	if (data->map.grid[(int)data->pos.y] \
	[(int)(data->pos.x - data->plane.x * data->move_speed)] == '0')
		data->pos.x -= data->plane.x * data->move_speed;
	if (data->map.grid[(int)(data->pos.y - data->plane.y * data->move_speed)] \
	[(int)data->pos.x] == '0')
		data->pos.y -= data->plane.y * data->move_speed;
}

void	move_right(t_data *data)
{
	if (data->map.grid[(int)data->pos.y] \
	[(int)(data->pos.x + data->plane.x * data->move_speed)] == '0')
		data->pos.x += data->plane.x * data->move_speed;
	if (data->map.grid[(int)(data->pos.y + data->plane.y * data->move_speed)] \
	[(int)data->pos.x] == '0')
		data->pos.y += data->plane.y * data->move_speed;
}
