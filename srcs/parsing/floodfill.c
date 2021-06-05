/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floodfill.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: naomisterk <naomisterk@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/05 16:33:51 by naomisterk    #+#    #+#                 */
/*   Updated: 2021/06/05 19:47:47 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <iterative_floodfill.h>

int	flood_fill(t_status *status, t_map *map, int y, int x)
{
	t_queue	*q;
	int		empty;

	empty = 0;
	q = queue_new(x, y);
	while (!empty)
	{
		if (!valid_coordinate(q->y, q->x, map->x, map->y))
			return (set_status(status, MAP_ERROR));
		check_surrounding(q, map, status);
		if (q->next == NULL || *status != SUCCESS)
			empty = 1;
		if (empty)
			queue_clear(&q, free);
		else
			q = remove_first(q);
	}
	return (1);
}

int	check_coordinate(t_i2vec pos, t_map *map, t_queue *q, t_status *status)
{
	if (!empty_coordinate(pos.y, pos.x, map))
		return (0);
	if (visited_coordinate(pos.y, pos.x, map))
		return (0);
	if (!queue_add_back(&q, pos.y, pos.x))
		return (set_status(status, MALLOC_ERROR));
	map->check[pos.y][pos.x] = '9';
	return (1);
}

void	check_surrounding(t_queue *q, t_map *map, t_status *status)
{
	check_coordinate((t_i2vec){q->x, q->y + 1}, map, q, status);
	check_coordinate((t_i2vec){q->x + 1, q->y + 1}, map, q, status);
	check_coordinate((t_i2vec){q->x - 1, q->y + 1}, map, q, status);
	check_coordinate((t_i2vec){q->x, q->y - 1}, map, q, status);
	check_coordinate((t_i2vec){q->x + 1, q->y - 1}, map, q, status);
	check_coordinate((t_i2vec){q->x - 1, q->y - 1}, map, q, status);
	check_coordinate((t_i2vec){q->x + 1, q->y}, map, q, status);
	check_coordinate((t_i2vec){q->x - 1, q->y}, map, q, status);
}
