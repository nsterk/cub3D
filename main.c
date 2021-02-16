/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 14:57:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/02/16 17:58:48 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

void	ft_mlx_pixel_put(int x, int y, int colour)
{
	char	*dst;

	dst = data.mlx.addr + (y * data.mlx.line_length + x * (data.mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}

void	put_line(int x1, int y1, int x2, int y2, int colour)
{
	int y;
	int x;
	int dx;
	int dy;
	int distance;

	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	distance = 2 * dy - dx;
	
	while (x <= x2)
	{
		ft_mlx_pixel_put(x, y, colour);
		if (distance > 0)
		{
			y++;
			distance -= 2 * dx;
		}
		else
			distance += 2 * dy;
		x++;
	}
}

static void	*start_mlx(t_mlx_data *mlx)
{
	data.do_mlx = mlx_init();
	if (!data.do_mlx)
		return (NULL);
	data.window = mlx_new_window(data.do_mlx, data.x_res, data.y_res, "mert");
	if (!data.window)
		return (NULL);
	mlx->img = mlx_new_image(data.do_mlx, data.x_res, data.y_res);
	if (!mlx->img)
		return (NULL);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	if (!mlx->addr)
		return (NULL);
	return ("1");
}

/*
void	init_environment(void)
{
	int x;
	int y;
	
	y = 0;
	while (y < data.y_res)
	{
		x = 0;
		while (x < data.x_res)
		{
			if (y < (data.y_res / 2))
				ft_mlx_pixel_put(x, y, 0x00c5c5c5);
			else
				ft_mlx_pixel_put(x, y, 0x007fbebe);
			x++;
		}
		y++;
	}
}
*/

void	draw_2d_map(void)
{
	int x;
	int y;
	int xo;
	int yo;

	x = 0;
	y = 0;
	while (y < map_y)
	{
		while (x < map_x)
		{
			xo = x * map_size;
			yo = y * map_size;
		}
	}
}

int		main(void)
{
	data.y_res = 512;
	data.x_res = 1024;
	start_mlx(&data.mlx);
	/*put_line(30, 0, 30, 50, 0x00c5c5c5);*/
	/*init_environment();*/
	mlx_put_image_to_window(data.do_mlx, data.window, data.mlx.img, 0, 0);
	mlx_loop(data.do_mlx);
	return (0);
}
