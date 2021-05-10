/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 15:27:40 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/10 15:29:22 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit_window(data);
	else if (keycode == D)
		data->keys.d = 1;
	else if (keycode == A)
		data->keys.a = 1;
	else if (keycode == W)
		data->keys.w = 1;
	else if (keycode == S)
		data->keys.s = 1;
	else if (keycode == LEFT)
		data->keys.left = 1;
	else if (keycode == RIGHT)
		data->keys.right = 1;
	return (1);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == D)
		data->keys.d = 0;
	else if (keycode == A)
		data->keys.a = 0;
	else if (keycode == W)
		data->keys.w = 0;
	else if (keycode == S)
		data->keys.s = 0;
	else if (keycode == LEFT)
		data->keys.left = 0;
	else if (keycode == RIGHT)
		data->keys.right = 0;
	return (1);
}
