/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/08 15:47:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/08 19:23:04 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

static void	free_validate(t_file *file)
{
	int	i;

	i = 0;
	while (i < file->map_y)
	{
		free(file->map_check[i]);
		i++;
	}
	free(file->map_check);
}

int	validate_map(t_file *file)
{
	int	i;

	i = 0;
	file->map_check = (char **)malloc(sizeof(char *) * (file->map_y + 1));
	if (!file->map_check)
		return (0);
	while (i < file->map_y)
	{
		file->map_check[i] = ft_strdup(file->map[i]);
		if (!file->map_check[i])
			return (0);
		i++;
	}
	if (!floodfill(file->spawn.y, file->spawn.x, file))
		return (0);
	free_validate(file);
	return (1);
}

int	floodfill(int y, int x, t_file *file)
{
	if (y == 0 || x == 0 || x == file->map_x[y] - 1
		|| y == file->map_y - 1)
	{
		printf("Invalid map\n");
		return (0);
	}
	if (file->map_check[y][x] == '0')
	{
		file->map_check[y][x] = '9';
		if (file->map_check[y - 1][x - 1] != '1')
			floodfill(y - 1, x - 1, file);
		if (file->map_check[y - 1][x] != '1')
			floodfill(y - 1, x, file);
		if (file->map_check[y - 1][x + 1] != '1')
			floodfill(y - 1, x + 1, file);
		if (file->map_check[y][x - 1] != '1')
			floodfill(y, x - 1, file);
		if (file->map_check[y][x + 1] != '1')
			floodfill(y, x + 1, file);
		if (file->map_check[y + 1][x - 1] != '1')
			floodfill(y + 1, x - 1, file);
		if (file->map_check[y + 1][x] != '1')
			floodfill(y + 1, x, file);
		if (file->map_check[y + 1][x + 1] != '1')
			floodfill(y + 1, x + 1, file);
	}
	return (1);
}
