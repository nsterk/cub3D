/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 15:58:54 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/12 18:34:16 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(int x, int y, int colour, t_img *img)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_pp / 8));
	*(unsigned int *)dst = colour;
}

void	put_line(int x, t_ray ray, int colour, t_img *img)
{
	while (ray.line_start < ray.line_end)
	{
		put_pixel(x, ray.line_start, colour, img);
		ray.line_start++;
	}
}
/*
t_colour	get_colour()
{
	t_colour	colour;
	char		*dst;
}
*/
