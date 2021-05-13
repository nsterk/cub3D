/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/08 15:47:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/13 18:31:50 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	validate_map(t_status *status, t_map *map, char **grid)
{
	int	i;

	i = 0;
	map->check = (char **)malloc(sizeof(char *) * (map->y + 1));
	if (!map->check)
		return (set_status(status, MALLOC_ERROR));
	while (i < map->y)
	{
		map->check[i] = ft_strdup(grid[i]);
		if (!map->check[i])
		{
			free_map(map, i);
			return (set_status(status, MALLOC_ERROR));
		}
		i++;
	}
	i = floodfill(map->spawn_pos.y, map->spawn_pos.x, map);
	free_map(map, 0);
	if (!i)
		return (set_status(status, MAP_ERROR));
	return (1);
}

int	floodfill(int y, int x, t_map *map)
{
	if (y == 0 || x == 0 || x == map->x[y] - 1
		|| y == map->y - 1)
		return (0);
	if (map->check[y][x] == '0')
	{
		map->check[y][x] = '9';
		if (map->check[y - 1][x - 1] != '1')
			floodfill(y - 1, x - 1, map);
		if (map->check[y - 1][x] != '1')
			floodfill(y - 1, x, map);
		if (map->check[y - 1][x + 1] != '1')
			floodfill(y - 1, x + 1, map);
		if (map->check[y][x - 1] != '1')
			floodfill(y, x - 1, map);
		if (map->check[y][x + 1] != '1')
			floodfill(y, x + 1, map);
		if (map->check[y + 1][x - 1] != '1')
			floodfill(y + 1, x - 1, map);
		if (map->check[y + 1][x] != '1')
			floodfill(y + 1, x, map);
		if (map->check[y + 1][x + 1] != '1')
			floodfill(y + 1, x + 1, map);
	}
	return (1);
}
