/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map_01.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:20:08 by nsterk        #+#    #+#                 */
/*   Updated: 2021/06/05 19:07:10 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	parse_map(t_data *data, int fd)
{
	if (!read_map(data, fd))
		return (0);
	if (!get_map_info(data))
		return (0);
	if (!validate_map(data))
		return (0);
	return (1);
}

int	read_map(t_data *data, int fd)
{
	char	*line;
	t_list	*head;

	head = ft_lstnew(ft_strdup(data->file.line));
	if (!head)
		return (set_status(&data->status, MALLOC_ERROR));
	while (data->file.ret > 0)
	{
		data->file.ret = get_next_line(fd, &line);
		if (data->file.ret < 0 || !ft_stradd_back(&head, ft_strdup(line)))
		{
			ft_lstclear(&head, free);
			return (set_status(&data->status, READ_ERROR));
		}
		free(line);
	}
	data->map.y = ft_lstsize(head);
	copy_map(head, data);
	ft_lstclear(&head, free);
	if (!data->map.grid)
		return (set_status(&data->status, MALLOC_ERROR));
	return (1);
}

int	copy_map(t_list *list, t_data *data)
{
	int		y;

	data->map.grid = (char **)malloc(sizeof(char *) * \
		(data->map.y + 1));
	if (!data->map.grid)
		return (set_status(&data->status, MALLOC_ERROR));
	y = 0;
	while (y < data->map.y)
	{
		data->map.grid[y] = ft_calloc(ft_strlen(list->content) + 2, \
		sizeof(char));
		if (!data->map.grid[y])
		{
			free_str_array(data->map.grid, y);
			return (set_status(&data->status, MALLOC_ERROR));
		}
		ft_strcpy(data->map.grid[y], list->content);
		list = list->next;
		y++;
	}
	return (1);
}
