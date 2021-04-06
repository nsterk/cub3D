/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:44:38 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/06 18:50:32 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static int	id_path(t_file *file, char *s)
{
	static const t_id	id[3] = {
		[0] = &parse_res,
		[1] = &colour,
	};

	return (((*(u_int16_t *)s == *(u_int16_t *) "R ") && id[0](file, s + 1))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "C ") && id[1](file, s))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "F ") && id[1](file, s)));
}

static char	first_char(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (*str);
}

static int	ready_for_map(t_file *file)
{
	if (file->res.x < 0 || file->res.y < 0)
		return (0);
	if (file->floor.R < 0 || file->floor.G < 0
		|| file->floor.B < 0)
		return (0);
	if (file->ceiling.R < 0 || file->ceiling.G < 0
		|| file->ceiling.B < 0)
		return (0);
	return (1);
}

int	parse_start(t_file *file)
{
	int		fd;
	int		ret;
	int		i;

	fd = open(file->str, O_RDONLY);
	if (fd < 0)
		return (0);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &file->line);
		i = 0;
		if (ft_isalpha(first_char(file->line)))
		{
			while (!ft_isalpha(file->line[i]))
				i++;
			if (!id_path(file, file->line + i))
				return (0);
		}
		else if (ready_for_map(file) && ft_isdigit(first_char(file->line)))
		{
			if (!parse_map(fd, file, ret))
				return (0);
			else
				ret = 0;
		}
		free(file->line);
	}
	close(fd);
	return (1);
}
