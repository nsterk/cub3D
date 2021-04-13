/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:44:38 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/13 17:52:09 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static int	id_path(t_data *data, char *s)
{
	static const t_id	id[3] = {
		[0] = &parse_res,
		[1] = &colour,
		[2] = &parse_tex,
	};

	return (((*(u_int16_t *)s == *(u_int16_t *) "R ") && id[0](data->res, s + 1))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "C ") && id[1](data, s))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "F ") && id[1](data, s))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "NO") && id[2](data->tex, s)));
}

static char	first_char(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (*str);
}

static int	ready_for_map(t_data *data)
{
	if (data->res.x < 0 || data->res.y < 0)
		return (0);
	if (data->file.floor.R < 0 || data->file.floor.G < 0
		|| data->file.floor.B < 0)
		return (0);
	if (data->file.ceiling.R < 0 || data->file.ceiling.G < 0
		|| data->file.ceiling.B < 0)
		return (0);
	return (1);
}

int	parse_start(t_data *data)
{
	int		fd;
	int		ret;
	int		i;

	fd = open(data->file.str, O_RDONLY);
	if (fd < 0)
		return (0);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &data->file.line);
		i = 0;
		if (ft_isalpha(first_char(&data->file.line)))
		{
			while (!ft_isalpha(data->file.line[i]))
				i++;
			if (!id_path(data, data->file.line + i))
				return (0);
		}
		else if (ready_for_map(data) && ft_isdigit(first_char(&data->file.line)))
		{
			if (!parse_map(fd, data, ret))
				return (0);
			else
				ret = 0;
		}
		free(data->file.line);
	}
	close(fd);
	return (1);
}
