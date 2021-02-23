/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_walls.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 17:49:24 by nsterk        #+#    #+#                 */
/*   Updated: 2021/02/23 17:54:04 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		check_walls_up(t_data *data)
{
	int y;
	int x;

	y = (data->y_pos - data->speed) / data->map_size - 1;
	x = data->x_pos / data->map_size - 1;
	if (map[y][x] == 1)
		return (1);
	return (0);
}