/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/08 15:47:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/28 16:55:25 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
/*
**	REMOVE HEADERS & GETUPTIME FUNCTION BEFORE SUBMISSION
*/
#include <time.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <CoreServices/CoreServices.h>
#include <stdio.h>

uint64_t getUptimeInMilliseconds(void)
{
    static mach_timebase_info_data_t s_timebase_info;

    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        (void) mach_timebase_info(&s_timebase_info);
    });
	return (uint64_t)((mach_absolute_time() * s_timebase_info.numer));
}

int	validate_map(t_data *data)
{
	uint64_t	begin, end;
	if (!allocate_check(&data->map))
		return (set_status(&data->status, MALLOC_ERROR));
	if (!copy_to_check(&data->map))
		return (set_status(&data->status, MAP_ERROR));
	begin = getUptimeInMilliseconds();
	floodfill(&data->status, data->pos.y, data->pos.x, &data->map);
	end = getUptimeInMilliseconds();
	printf("That took %llu \n", end - begin);
	free_str_array(data->map.check, data->map.y);
	if (data->status != SUCCESS)
		return (0);
	return (1);
}

int	allocate_check(t_map *map)
{
	int	y;
	int	x;
	int	len;

	y = 0;
	len = get_largest_number(map->x, map->y);
	map->check = (char **)malloc(sizeof(char *) * map->y);
	if (!map->check)
		return (0);
	while (y < map->y)
	{
		x = 0;
		map->check[y] = ft_calloc(len, sizeof(char));
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

// void	floodfill(t_status *status, int y, int x, t_map *map)
// {
// 	if (y == 0 || x == 0 || x >= map->x[y] - 1 || y >= map->y - 1)
// 	{
// 		set_status(status, MAP_ERROR);
// 		return ;
// 	}
// 	if (map->check[y][x] == '0')
// 	{
// 		map->check[y][x] = '9';
// 		if (map->check[y + 1][x] != '1')
// 			floodfill(status, y + 1, x, map);
// 		if (map->check[y + 1][x + 1] != '1')
// 			floodfill(status, y + 1, x + 1, map);
// 		if (map->check[y + 1][x - 1] != '1')
// 			floodfill(status, y + 1, x - 1, map);
// 		if (map->check[y - 1][x] != '1')
// 			floodfill(status, y - 1, x, map);
// 		if (map->check[y - 1][x + 1] != '1')
// 			floodfill(status, y - 1, x + 1, map);
// 		if (map->check[y - 1][x - 1] != '1')
// 			floodfill(status, y - 1, x - 1, map);
// 		if (map->check[y][x + 1] != '1')
// 			floodfill(status, y, x + 1, map);
// 		if (map->check[y][x - 1] != '1')
// 			floodfill(status, y, x - 1, map);
// 	}
// }

/*
**	Als ik deze recursieve floodfill hou: volgens mij is de if (map-check == 0) statement
**	nu overbodig. Moet dus nog weg.
*/

void	floodfill(t_status *status, int y, int x, t_map *map)
{
	if (y == 0 || x == 0 || x >= map->x[y] - 1 || y >= map->y - 1)
	{
		set_status(status, MAP_ERROR);
		return ;
	}
	if (map->check[y][x] == '0')
	{
		map->check[y][x] = '9';
		if (map->check[y + 1][x] != '1' && map->check[y + 1][x] != '9')
			floodfill(status, y + 1, x, map);
		if (map->check[y + 1][x + 1] != '1' && map->check[y + 1][x + 1] != '9')
			floodfill(status, y + 1, x + 1, map);
		if (map->check[y + 1][x - 1] != '1' && map->check[y + 1][x - 1] != '9')
			floodfill(status, y + 1, x - 1, map);
		if (map->check[y - 1][x] != '1' && map->check[y - 1][x] != '9')
			floodfill(status, y - 1, x, map);
		if (map->check[y - 1][x + 1] != '1' && map->check[y - 1][x + 1] != '9')
			floodfill(status, y - 1, x + 1, map);
		if (map->check[y - 1][x - 1] != '1' && map->check[y - 1][x - 1] != '9')
			floodfill(status, y - 1, x - 1, map);
		if (map->check[y][x + 1] != '1' && map->check[y][x + 1] != '9')
			floodfill(status, y, x + 1, map);
		if (map->check[y][x - 1] != '1' && map->check[y][x - 1] != '9')
			floodfill(status, y, x - 1, map);
	}
}
