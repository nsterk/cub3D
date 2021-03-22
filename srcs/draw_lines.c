/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_lines.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 15:21:37 by nsterk        #+#    #+#                 */
/*   Updated: 2021/02/24 15:48:29 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_line_low(int x0, int y0, int x1, int y1, t_data *data)
{
	int dx;
	int dy;
	int yi;
	int dist;

	dx = x1 - x0;
	dy = y1 - y0;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	dist = (2 * dy) - dx;
	while (x0 <= x1)
	{
		put_pixel(x0, y0, 0x00FFFF00, data);
		if (dist > 0)
		{
			y0 += yi;
			dist += (2 * (dy - dx));
		}
		else
			dist += (2 * dy);
	}
}

void	put_line_high(int x0, int y0, int x1, int y1, t_data *data)
{
	int dx;
	int dy;
	int xi;
	int dist;

	dx = x1 - x0;
	dy = y1 - y0;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	dist = (2 * dx) - dy;
	while (y0 <= y1)
	{
		put_pixel(x0, y0, 0x00FFFF00, data);
		if (dist > 0)
		{
			x0 += xi;
			dist += (2 * (dx - dy));
		}
		else
			dist += (2 * dx);
	}
}

void	put_line(int x0, int y0, int x1, int y1, t_data *data)
{
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			put_line_low(x1, y1, x0, y0, data);
		else
			put_line_low(x0, y0, x1, y1, data);
	}
	else
		if (y0 > y1)
			put_line_high(x1, y1, x0, y0, data);
		else
			put_line_high(x0, y0, x1, y1, data);
}