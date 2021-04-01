/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:20:08 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/01 19:36:31 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

int	parse_map(int fd, t_file *file, int ret)
{
	char	*line;
	t_list	*head;
	t_list	*temp;

	head = ft_lstnew(ft_strcdup(file->line, ' '));
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (1);
		ft_stradd_back(&head, ft_strcdup(line, ' '));
		free(line);
	}
	temp = head;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	return (0);
}
/*
char	**alloc_map(int n, char **old)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(**new) * (n + 2));
	if (!new)
	return (NULL);
	while (old[i] != NULL)
	{
		new[i] = ft_strdup(old[i]);
		free(old[i]);
		i++;
	}
	free(old);
	return (new);
}
*/