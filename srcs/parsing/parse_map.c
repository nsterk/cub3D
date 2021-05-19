/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:20:08 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/19 20:27:07 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	parse_map(t_data *data, int fd)
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
	data->map.y = ft_lstsize(head) - 1;
	data->map.grid = copy_map(&data->status, head, data->map.y);
	ft_lstclear(&head, free);
	if (!data->map.grid)
		return (set_status(&data->status, MALLOC_ERROR));
	if (!get_map_info(data))
		return (0);
	if (!validate_map(data))
		return (0);
	return (1);
}

char	**copy_map(t_status *status, t_list *list, int size)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * size + 1);
	if (!map)
	{
		*status = MALLOC_ERROR;
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		map[i] = ft_strdup(list->content);
		if (!map[i])
		{
			*status = MALLOC_ERROR;
			return (NULL);
		}
		list = list->next;
		i++;
	}
	return (map);
}

static int	get_spawn_info(t_data *data, int y)
{
	int	x;

	x = 0;
	while (x < (data->map.x[y] - 1))
	{
		if (data->map.grid[y][x] == '2')
			data->spr.amount++;
		else if (ft_strchr("NSEW", data->map.grid[y][x]))
		{
			if (data->map.spawn_char != '@')
				return (set_status(&data->status, MAP_ERROR));
			data->map.spawn_char = data->map.grid[y][x];
			data->pos = (t_d2vec){x + 0.5, y + 0.5};
			data->map.grid[y][x] = '0';
		}
		x++;
	}
	return (1);
}

static void	set_spawn_dir(char c, t_d2vec *dir, t_d2vec *plane)
{
	if (c == 'N')
	{
		*dir = (t_d2vec){0, -1};
		*plane = (t_d2vec){0.66, 0};
	}
	else if (c == 'E')
	{
		*dir = (t_d2vec){1, 0};
		*plane = (t_d2vec){0, 0.66};
	}
	else if (c == 'S')
	{
		*dir = (t_d2vec){0, 1};
		*plane = (t_d2vec){-0.66, 0};
	}
	else
	{
		*dir = (t_d2vec){-1, 0};
		*plane = (t_d2vec){0, -0.66};
	}
}

	get_map_info(t_data *data)
{
	int	i;

	i = 0;
	data->map.x = malloc(sizeof(int) * (data->map.y + 1));
	if (!data->map.x )
		return (set_status(&data->status, MALLOC_ERROR));
	while (i < data->map.y)
	{
		data->map.x[i] = (int)ft_strlen(data->map.grid[i]) + 1;
		if (!get_spawn_info(data, i))
			return (0);
		i++;
	}
	set_spawn_dir(data->map.spawn_char, &data->dir, &data->plane);
	data->map.x[i] = 0;
	return (1);
}
