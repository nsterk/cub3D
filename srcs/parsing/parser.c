/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:44:38 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/19 19:54:10 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <fcntl.h>
#include <unistd.h>

static int	id_path(t_data *data, char *s)
{
	static const t_id	id[4] = {
		[0] = &parse_res,
		[1] = &colour,
		[2] = &parse_tex,
		[3] = &parse_sprite,
	};

	return (((*(u_int16_t *)s == *(u_int16_t *) "R ") && id[0](data, s + 1))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "C ") && id[1](data, s))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "F ") && id[1](data, s))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "NO") && id[2](data, s))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "EA") && id[2](data, s))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "SO") && id[2](data, s))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "WE") && id[2](data, s))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "S ") && id[3](data, s)));
}

int	parser(t_data *data, int fd)
{
	int	i;

	while (data->file.ret > 0)
	{
		data->file.ret = get_next_line(fd, &data->file.line);
		i = 0;
		if (!ft_strchr("RCFNSWE01", first_char(data->file.line)))
			return (set_status(&data->status, CONFIG_ERROR));
		if (ft_isalpha(first_char(data->file.line)))
		{
			while (!ft_isalpha(data->file.line[i]))
				i++;
			if (!id_path(data, data->file.line + i))
				return (set_status(&data->status, CONFIG_ERROR));
		}
		else if (ready_for_map(data) && ft_isdigit(first_char(data->file.line)))
			parse_map(data, fd);
		free(data->file.line);
	}
	return (1);
}

int	parsing(t_data *data)
{
	int		fd;

	fd = open(data->file.path, O_RDONLY);
	if (fd < 0)
		return (set_status(&data->status, FILE_ERROR));
	parser(data, fd);
	close(fd);
	if (data->status != SUCCESS)
		return (0);
	return (complete_data(data));
}
