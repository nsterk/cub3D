/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterative_floodfill.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 16:53:07 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/27 19:57:15 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATIVE_FLOODFILL_H
# define ITERATIVE_FLOODFILL_H

typedef struct s_queue
{
	int				*x;
	int				*y;
	struct s_queue	*next;
}					t_queue;


t_queue		*queue_add_back(t_queue **queue, int y, int x);
void		queue_clear(t_queue **queue, void (*del)(void *));
void		queue_delone(t_queue *queue, void (*del)(void *));
t_queue		*queue_last(t_queue *queue);
t_queue		*queuemap(t_queue *queue, void *(*f)(void *),
				void (*del)(void *));
t_queue		*queue_new(int x, int y);
int			queue_size(t_queue *queue);
int			valid_coordinate(int y, int x, int *map_x, int map_y);

#endif