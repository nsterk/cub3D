/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:20:08 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/11 20:02:44 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_status	parse_map(t_data *data)
{
	char	*line;
	t_list	*head;

	head = ft_lstnew(ft_strdup(data->file.line)); // MALLOC
	while (data->file.ret > 0)
	{
		data->file.ret = get_next_line(data->file.fd, &line);
		if (data->file.ret < 0)
			return (MALLOC_ERROR);  // ERROR
		ft_stradd_back(&head, ft_strdup(line));
		free(line);
	}
	data->map.y = ft_lstsize(head);
	data->map.grid = copy_map(head, data->map.y);
	if (!data->map.grid)
		return (0);
	ft_lstclear(&head, free);
	if (!get_map_info(&data->map))  // ERROR
		return (0);
	if (!validate_map(&data->map, data->map.grid))  // ERROR
		return (0);
	return (1);
}

char	**copy_map(t_list *list, int size)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * (size + 1));
	if (!map)
		return (NULL);  // ERROR
	i = 0;
	while (list)
	{
		map[i] = ft_strdup(list->content);  // ERROR
		list = list->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

static int	get_spawn_info(t_map *map, int y)
{
	int	x;

	x = 0;
	while (x < map->x[y])
	{
		if (map->grid[y][x] == '2')
			map->nr_sprites++;
		else if (ft_strchr("NSEW", map->grid[y][x]))
		{
			if (map->spawn_char != '@') // ERROR
				return (0);
			map->spawn_char = map->grid[y][x];
			map->spawn_pos = (t_d2vec){x + 0.5, y + 0.5};
			map->grid[y][x] = '0';
		}
		x++;
	}
	return (1);
}

static void	set_spawn_dir(t_map *map)
{
	if (map->spawn_char == 'N')
	{
		map->spawn_dir = (t_d2vec){0, -1};
		map->plane = (t_d2vec){0.66, 0};
	}
	else if (map->spawn_char == 'E')
	{
		map->spawn_dir = (t_d2vec){1, 0};
		map->plane = (t_d2vec){0, 0.66};
	}
	else if (map->spawn_char == 'S')
	{
		map->spawn_dir = (t_d2vec){0, 1};
		map->plane = (t_d2vec){-0.66, 0};
	}
	else
	{
		map->spawn_dir = (t_d2vec){-1, 0};
		map->plane = (t_d2vec){0, -0.66};
	}
}

	get_map_info(t_map *map)
{
	int	i;

	i = 0;
	map->x = malloc(sizeof(int) * (map->y + 1));
	if (!map->x)
		return (0);
	while (i < map->y)
	{
		map->x[i] = (int)ft_strlen(map->grid[i]);
		if (!get_spawn_info(map, i))
			return (0);
		i++;
	}
	set_spawn_dir(map);
	map->x[i] = 0;
	return (1);
}
