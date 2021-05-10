/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:44:38 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/10 20:28:29 by nsterk        ########   odam.nl         */
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

static int	ready_for_map(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].path == NULL)
			return (0);
		i++;
	}
	if (data->spr.path == NULL)
		return (0);
	if (data->res.x < 0 || data->res.y < 0)
		return (0);
	if (data->floor < 0 || data->ceiling < 0)
		return (0);
	return (1);
}
/*
**	if error: FREE data->file.line	CLOSE data->file.fd
*/

int	parse_start(t_data *data)
{
	int		i;

	data->file.fd = open(data->file.path, O_RDONLY);
	if (data->file.fd < 0)
		return (0);
	while (data->file.ret > 0)
	{
		data->file.ret = get_next_line(data->file.fd, &data->file.line);
		i = 0;
		if (ft_isalpha(first_char(data->file.line)))
		{
			while (!ft_isalpha(data->file.line[i]))
				i++;
			if (!id_path(data, data->file.line + i))
				return (0);
		}
		else if (ready_for_map(data) && ft_isdigit(first_char(data->file.line)))
		{
			if (!parse_map(data))
				return (0);
		}
		free(data->file.line);
	}
	close(data->file.fd);
	return (1);
}
