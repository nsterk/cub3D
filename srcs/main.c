/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 14:57:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/02/23 19:50:29 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>
#include <math.h>

int			map_size = 64;
int			map_x = 8;
int			map_y = 8;
int			map[8][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

int		exit_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(1);
	return (1);
}

void	put_pixel(int x, int y, int colour, t_data *data)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}

static void	*start_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (NULL);
	data->window = mlx_new_window(data->mlx, data->x_res, data->y_res, "mert");
	if (!data->window)
		return (NULL);
	data->img.img_ptr = mlx_new_image(data->mlx, data->x_res, data->y_res);
	if (!data->img.img_ptr)
		return (NULL);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	if (!data->img.addr)
		return (NULL);
	return ("1");
}

int		keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit_window(data);
	if (keycode == W)
	{
		if (map[(data->y_pos - data->speed) / map_size][data->x_pos / map_size] != 1)
			data->y_pos -= data->speed;
	}
	if (keycode == S)
		if (map[(data->y_pos + data->speed) / map_size][data->x_pos / map_size] != 1)
			data->y_pos += data->speed;
	if (keycode == A)
		if (map[data->y_pos / map_size][(data->x_pos - data->speed)/ map_size] != 1)
			data->x_pos -= data->speed;
	if (keycode == D)
		if (map[data->y_pos / map_size][(data->x_pos + data->speed)/ map_size] != 1)
			data->x_pos += data->speed;
	return (1);
}

void	init_environment(t_data *data)
{
	int x;
	int y;
	
	y = 0;
	while (y < data->y_res)
	{
		x = 0;
		while (x < data->x_res)
		{
			put_pixel(x, y, 0x00c5c5c5, data);
			/*
			if (y < (data.y_res / 2))
				put_pixel(x, y, 0x00c5c5c5);
			else
				put_pixel(x, y, 0x007fbebe);
			*/
			x++;
		}
		y++;
	}
}

void	draw_cube(int x1, int x2, int y1, int y2, int colour, t_data *data)
{
	int x;
	
	while (y1 < y2)
	{
		x = x1;
		while (x < x2)
		{
			put_pixel(x, y1, colour, data);
			x++;
		}
		y1++;
	}
}

int	draw_player(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			put_pixel(data->x_pos + x, data->y_pos + y, 0x00FF0000, data);
			x++;
		}
		y++;
	}
	return (1);
}

int		draw_2d_map(t_data *data)
{
	int x;
	int y;
	int xo;
	int yo;
	
	y = 0;
	while (y < map_y)
	{
		x = 0;
		while (x < map_x)
		{
			xo = x * map_size;
			yo = y * map_size;
			if (map[y][x] == 1)
				draw_cube(xo + 1, xo + map_size - 1, yo + 1, yo + map_size - 1, WHITE, data);
			else
				draw_cube(xo + 1, xo + map_size - 1, yo + 1, yo + map_size - 1, BLACK, data);
			x++;
		}
		y++;
	}
	return (1);
}

int		window_loop(t_data *data)
{
	/*	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->img.img_ptr);	*/
	draw_2d_map(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img_ptr, 0, 0);
	/*	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data->window);	*/
	return (1);
}

int		loops(t_data *data)
{
	mlx_hook(data->window, 17, 0L, exit_window, data);
	mlx_hook(data->window, 2, (1L << 0), keypress, data);
	mlx_loop_hook(data->mlx, window_loop, data);
	mlx_loop(data->mlx);
	return (0);
}

int		main(void)
{
	t_data		data;

	init_data(&data);
	start_mlx(&data);
	init_environment(&data);
	loops(&data);
	return (0);
}
