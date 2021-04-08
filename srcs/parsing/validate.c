/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/08 15:47:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/08 15:56:39 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	floodfill(int y, int x, char **map)
{
	if (y == 0 || x == 0)
		return (0);
	if (map[y][x] == '0')
	{
		if (map[y - 1][x - 1] != '1')
			floodfill(y - 1, x - 1, map);
		if (map[y - 1][x] != '1')
			floodfill(y - 1, x, map);
		if (map[y - 1][x + 1] != '1')
			floodfill(y - 1, x + 1, map);
		if (map[y][x - 1] != '1')
			floodfill(y, x - 1, map);
		if (map[y][x + 1] != '1')
			floodfill(y, x + 1, map);
		if (map[y + 1][x - 1] != '1')
			floodfill(y + 1, x - 1, map);
		if (map[y + 1][x] != '1')
			floodfill(y + 1, x, map);
		if (map[y + 1][x + 1] != '1')
			floodfill(y + 1, x + 1, map);
	}
}
