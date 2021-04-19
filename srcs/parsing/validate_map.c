/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/08 15:47:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/19 13:35:53 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

static void	free_validate(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->y)
	{
		free(map->check[i]);
		i++;
	}
	free(map->check);
}

int	validate_map(t_map *map, char **grid)
{
	int	i;

	i = 0;
	map->check = (char **)malloc(sizeof(char *) * (map->y + 1));
	if (!map->check)
		return (0);
	while (i < map->y)
	{
		map->check[i] = ft_strdup(grid[i]);
		if (!map->check[i])
			return (0);
		i++;
	}
	if (!floodfill(map->spawn_pos.y, map->spawn_pos.x, map))
		return (0);
	free_validate(map);
	return (1);
}

int	floodfill(int y, int x, t_map *map)
{
	if (y == 0 || x == 0 || x == map->x[y] - 1
		|| y == map->y - 1)
	{
		printf("Invalid map\n");
		return (0);
	}
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
