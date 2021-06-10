/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floodfill_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: naomisterk <naomisterk@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/05 16:33:51 by naomisterk    #+#    #+#                 */
/*   Updated: 2021/06/10 09:55:15 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <iterative_floodfill.h>

int	valid_coordinate(int y, int x, int *map_x, int map_y)
{
	if (y == 0 || x == 0)
		return (0);
	else if (x >= map_x[y] - 1 || y >= map_y - 1)
		return (0);
	return (1);
}

t_queue	*remove_first(t_queue *q)
{
	t_queue	*temp;

	temp = q->next;
	queue_delone(q, free);
	return (temp);
}
