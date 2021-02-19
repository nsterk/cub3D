/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 13:11:35 by nsterk        #+#    #+#                 */
/*   Updated: 2021/02/19 14:14:05 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_data(t_data *data)
{
	data->y_res = 600;
	data->x_res = 1024;
	data->y_pos = 100;
	data->x_pos = 100;
/*
	data->map.map_x = 8;
	data->map.map_y = 8;
	data->map.map_size = 64;*/
}