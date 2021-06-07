/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterative_floodfill.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 16:53:07 by nsterk        #+#    #+#                 */
/*   Updated: 2021/06/06 15:12:48 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATIVE_FLOODFILL_H
# define ITERATIVE_FLOODFILL_H

typedef struct s_queue
{
	int				x;
	int				y;
	struct s_queue	*next;
}					t_queue;

t_queue	*queue_add_back(t_queue **queue, int y, int x);
void	queue_clear(t_queue **queue, void (*del)(void *));
void	queue_delone(t_queue *queue, void (*del)(void *));
t_queue	*queue_last(t_queue *queue);
t_queue	*queuemap(t_queue *queue, void *(*f)(void *), void (*del)(void *));
t_queue	*queue_new(int x, int y);
int		queue_size(t_queue *queue);
int		check_surrounding(t_queue *q, t_map *map, t_status *status);
int		valid_coordinate(int y, int x, int *map_x, int map_y);
int		check_coordinate(t_i2vec pos, t_map *map, t_queue *q, t_status *status);
int		flood_fill(t_status *status, t_map *map, int y, int x);
t_queue	*remove_first(t_queue *q);

#endif