/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   queue.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 14:54:17 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/27 19:57:09 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <iterative_floodfill.h>

t_queue	*queue_add_back(t_queue **queue, int y, int x)
{
	t_queue	*new;
	t_queue	*temp;

	new = queue_new(x, y);
	if (!new)
		return (NULL);
	if (*queue == NULL)
		*queue = new;
	else
	{
		temp = queue_last(*queue);
		temp->next = new;
	}
	return (new);
}

t_queue	*queue_new(int x, int y)
{
	t_queue	*new;

	new = malloc(sizeof(t_queue));
	if (!new)
		return (NULL);
	new->x = malloc(sizeof(int));
	*new->x = x;
	new->y = malloc(sizeof(int));
	*new->y = y;
	new->next = NULL;
	return (new);
}

t_queue	*queue_last(t_queue *queue)
{
	if (!queue)
		return (NULL);
	while (queue->next)
		queue = queue->next;
	return (queue);
}

void	queue_clear(t_queue **queue, void (*del)(void *))
{
	t_queue	*temp;

	if (!queue)
		return ;
	while (*queue)
	{
		temp = (*queue)->next;
		queue_delone(*queue, del);
		*queue = temp;
	}
}

void	queue_delone(t_queue *queue, void (*del)(void*))
{
	if (!queue || !del)
		return ;
	del(queue->x);
	del(queue->y);
	free(queue);
}

/*

int main(void)
{
	t_queue	*head;
	t_queue	*temp;
	int x;
	int y;

	x = 1;
	y = 0;
	head = queue_new(x, y);
	queue_add_back(&head, x + 1, y + 1);
	temp = head;
	while (temp)
	{
		printf("%i, %i\n", *temp->x, *temp->y);
		temp = temp->next;
	}
	return (0);
}
*/