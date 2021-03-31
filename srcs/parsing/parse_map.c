/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 17:20:08 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/01 00:32:58 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	parse_map(int fd, char *str, t_file *file, int ret)
{
char	*line;i9    
t_list	*head;

head = ft_lstnew(str);
while (ret > 0)
{
ret = get_next_line(fd, &line);
if (ret < 0)
	return (1);
ft_stradd_back(&head, ft_strdup(line));
free(line);
}
}

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
