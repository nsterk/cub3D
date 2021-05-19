/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/08 15:47:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/18 20:17:38 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	validate_map(t_status *status, t_map *map, char **grid)
{
	if (!allocate_check(status, map))
		return (set_status(status, MALLOC_ERROR));
	if (!copy_to_check(map))
		return (set_status(status, MAP_ERROR));
	floodfill(status, map->spawn_pos.y, map->spawn_pos.x, map);
	free_map(map, 0);
	if (*status != SUCCESS)
		return (0);
	return (1);
}

int	allocate_check(t_status *status, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	map->check = (char **)malloc(sizeof(char *) * map->y);
	if (!map->check)
		return (0);
	while (y < map->y)
	{
		x = 0;
		map->check[y] = (char *)malloc(sizeof(char) * map->x[y]);
		if (!map->check[y])
		{
			free_map(map, y);
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
			if (!ft_strchr("012", map->grid[y][x]))
				return (0);
			map->check[y][x] = map->grid[y][x];
			if (map->check[y][x] == '2')
				map->check[y][x] = '0';
			x++;
		}
		y++;
	}
	return (1);
}

// int	validate_map(t_status *status, t_map *map, char **grid)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	map->check = (char **)malloc(sizeof(char *) * (map->y + 1));
// 	if (!map->check)
// 		return (set_status(status, MALLOC_ERROR));
// 	while (y < map->y)
// 	{
// 		x = 0;
// 		map->check[y] = ft_strdup(grid[y]);
// 		if (!map->check[y])
// 		{
// 			free_map(map, y);
// 			return (set_status(status, MALLOC_ERROR));
// 		}
// 		while (x < map->x[y])
// 		{
// 			if (map->check[y][x] == '2')
// 				map->check[y][x] = '0';
// 			x++;
// 		}
// 		y++;
// 	}
// 	floodfill(status, map->spawn_pos.y, map->spawn_pos.x, map);
// 	free_map(map, 0);
// 	if (*status != SUCCESS)
// 		return (0);
// 	return (1);
// }

void	floodfill(t_status *status, int y, int x, t_map *map)
{
	if (y == 0 || x == 0 || x == map->x[y] - 1 || y == map->y - 1)
	{
		set_status(status, MAP_ERROR);
		return ;
	}
	if (map->check[y][x] == '0')
	{
		map->check[y][x] = '9';
		if (map->check[y + 1][x] != '1')
			floodfill(status, y + 1, x, map);
		if (map->check[y + 1][x + 1] != '1')
			floodfill(status, y + 1, x + 1, map);
		if (map->check[y + 1][x - 1] != '1')
			floodfill(status, y + 1, x - 1, map);
		if (map->check[y - 1][x] != '1')
			floodfill(status, y - 1, x, map);
		if (map->check[y - 1][x + 1] != '1')
			floodfill(status, y - 1, x + 1, map);
		if (map->check[y - 1][x - 1] != '1')
			floodfill(status, y - 1, x - 1, map);
		if (map->check[y][x + 1] != '1')
			floodfill(status, y, x + 1, map);
		if (map->check[y][x - 1] != '1')
			floodfill(status, y, x - 1, map);
	}
}
