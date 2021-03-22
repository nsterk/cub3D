/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 15:58:54 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/03 06:35:50 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(int x, int y, int colour, t_img *img)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_pp / 8));
	*(unsigned int *)dst = colour;
}

void	put_line(int x, int y0, int y1, int colour, t_img *img)
{
	while (y0 < y1)
	{
		put_pixel(x, y0, colour, img);
		y0++;
	}
}
