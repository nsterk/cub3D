/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:20:08 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/08 18:58:41 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

int	parse_map(int fd, t_file *file, int ret)
{
	char	*line;
	t_list	*head;

	head = ft_lstnew(ft_strdup(file->line));
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (0);
		ft_stradd_back(&head, ft_strdup(line));
		free(line);
	}
	file->map_y = ft_lstsize(head);
	file->map = copy_map(head, file->map_y);
	if (!file->map)
		return (0);
	ft_lstclear(&head, free);
	file->map_x = get_width(file);
	if (!validate_map(file))
		return (0);
	return (1);
}

char	**copy_map(t_list *list, int size)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * (size + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (list)
	{
		map[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

int		*get_width(t_file *file)
{
	int	i;
	int	*map_x;

	i = 0;
	map_x = malloc(sizeof(int) * (file->map_y + 1));
	if (!map_x)
		return (NULL);
	while (i < file->map_y)
	{
		map_x[i] = (int)ft_strlen(file->map[i]);
		i++;
	}
	map_x[i] = 0;
	return (map_x);
}
