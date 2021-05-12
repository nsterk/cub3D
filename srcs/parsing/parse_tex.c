/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 18:26:56 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/12 04:48:12 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	fill_tex_paths(char *s, t_img *img, t_status *status)
{
	img->path = ft_strtrim(s + 2, " \t\n\f\r\v");
	if (!img->path)
		return (set_status(status, MALLOC_ERROR));
	return (1);
}

int	parse_tex(t_data *data, char *line)
{
	if (!is_space(line + 2))
		return (set_status(&data->status, CONFIG_ERROR));
	else if (*line == 'N')
		return (fill_tex_paths(line, &data->tex[0].img, &data->status));
	else if (*line == 'E')
		return (fill_tex_paths(line, &data->tex[1].img, &data->status));
	else if (*line == 'S')
		return (fill_tex_paths(line, &data->tex[2].img, &data->status));
	else if (*line == 'W')
		return (fill_tex_paths(line, &data->tex[3].img, &data->status));
	return (1);
}

int	parse_sprite(t_data *data, char *line)
{
	data->spr.img.path = ft_strtrim(line + 1, " \t\n\f\r\v");
	if (!data->spr.img.path)
		return (0);
	return (1);
}
