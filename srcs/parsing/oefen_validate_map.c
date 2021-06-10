/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   oefen_validate_map.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/08 15:47:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/06/10 10:51:29 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <iterative_floodfill.h>

int	validate_map(t_data *data)
{
	if (!allocate_check(&data->map))
		return (set_status(&data->status, MALLOC_ERROR));
	if (!copy_to_check(&data->map))
		return (set_status(&data->status, MAP_ERROR));
	floodfill(&data->status, &data->map, data->pos.y, data->pos.x);
	free_str_array(data->map.check, data->map.y);
	if (data->status != SUCCESS)
		return (0);
	return (1);
}

int	allocate_check(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	map->max_x = get_largest_number(map->x, map->y);
	map->check = (char **)malloc(sizeof(char *) * map->y);
	if (!map->check)
		return (0);
	while (y < map->y)
	{
		x = 0;
		map->check[y] = ft_calloc(map->max_x, sizeof(char));
		if (!map->check[y])
		{
			free_str_array(map->check, y);
			return (0);
		}
		y++;
	}
	return (1);
}

int	copy_to_check(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x[y])
		{
			if (!ft_strchr("012 ", map->grid[y][x]))
			{
				free_str_array(map->check, map->y);
				return (0);
			}
			if (map->grid[y][x] == ' ')
				map->grid[y][x] = '1';
			map->check[y][x] = map->grid[y][x];
			if (map->check[y][x] == '2')
				map->check[y][x] = '0';
			x++;
		}
		y++;
	}
	return (1);
}
