/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:20:08 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/19 13:43:23 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	parse_map(int fd, t_data *data, int ret)
{
	char	*line;
	t_list	*head;

	head = ft_lstnew(ft_strdup(data->file.line));
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (0);
		ft_stradd_back(&head, ft_strdup(line));
		free(line);
	}
	data->map.y = ft_lstsize(head);
	data->map.grid = copy_map(head, data->map.y);
	if (!data->map.grid)
		return (0);
	ft_lstclear(&head, free);
	if (!get_map_info(&data->map))
		return (0);
	if (!validate_map(&data->map, data->map.grid))
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

int	get_map_info(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->x = malloc(sizeof(int) * (map->y + 1));
	if (!map->x)
		return (0);
	while (i < map->y)
	{
		map->x[i] = (int)ft_strlen(map->grid[i]);
		while (j < map->x[i])
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
			{
				if (map->spawn_char != '1')
					return (0);
				map->spawn_char = map->grid[i][j];
				map->spawn_pos = (t_i2vec){j, i};
			}
			j++;
		}
		j = 0;
		i++;
	}
	map->x[i] = 0;
	return (1);
}
