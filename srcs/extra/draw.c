/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 15:58:54 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/07 13:12:29 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	put_pixel(int x, int y, int colour, t_img *img)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = colour;
}

void	put_line(int x, t_ray *ray, int colour, t_img *img)
{
	while (ray->line_start < ray->line_end)
	{
		put_pixel(x, ray->line_start, colour, img);
		ray->line_start++;
	}
}
