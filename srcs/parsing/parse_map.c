/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:20:08 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/29 17:20:56 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	parse_map(int fd, char *str, t_file *file, int ret)
{
	int		n;

	n = 1;
	file->map = (char **)malloc(sizeof(char *) * 2);
	if (!file->map)
		return (1);
	file->map[0] = ft_strcdup(str, ' ');
	if (!file->map[0])
		return (1);
	file->map[1] = NULL;
	while (ret > 0)
	{
		file->map = alloc_map(n, file->map);
		ret = get_next_line(fd, &file->map[n]);
		n++;
	}
}

char	**alloc_map(int n, char **old)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(**new), n + 2);
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
