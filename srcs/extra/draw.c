/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 15:58:54 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/18 19:33:17 by nsterk        ########   odam.nl         */
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

void	apply_shade(t_sprite *spr, t_colour *colour)
{
	colour->parts.B = colour->parts.B / (spr->transform.y / 10.0 + 1.0);
	colour->parts.G = colour->parts.G / (spr->transform.y / 10.0 + 1.0);
	colour->parts.R = colour->parts.R / (spr->transform.y / 10.0 + 1.0);
	colour->parts.T = 0;
}

t_colour	get_colour(t_sprite *spr)
{
	t_colour	colour;
	char		*dst;

	dst = spr->img.addr + (spr->tex.y * spr->img.len \
		 + spr->tex.x * (spr->img.bpp / 8));
	colour.colour = *(unsigned int *)dst;
	return (colour);
}
