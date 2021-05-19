/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_sprites.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 17:54:52 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/19 17:33:29 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	position_sprites(char **map, t_d2vec *pos, int *xmax, int ymax)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (y < ymax)
	{
		x = 0;
		while (x < xmax[y])
		{
			if (map[y][x] == '2')
			{
				pos[i] = (t_d2vec){x + 0.5, y + 0.5};
				i++;
			}
			x++;
		}
		y++;
	}
}

int	complete_sprites(t_data *data)
{
	data->spr.amount = data->map.nr_sprites;
	data->spr.pos = malloc(sizeof(t_d2vec) * data->spr.amount);
	if (!data->spr.pos)
		return (set_status(&data->status, MALLOC_ERROR));
	data->spr.distance = malloc(sizeof(double) * data->spr.amount);
	if (!data->spr.distance)
		return (set_status(&data->status, MALLOC_ERROR));
	position_sprites(data->map.grid, data->spr.pos, data->map.x, data->map.y);
	return (1);
}
