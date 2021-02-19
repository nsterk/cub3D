/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 14:57:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/02/19 14:43:13 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

void	init_data(t_data *data)
{
	data->obj_height = 30;
	data->obj_width = 30;
	data->y_res = 480;
	data->x_res = 800;
	data->y_pos = 210;
	data->x_pos = 370;
}

int		exit_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(1);
	return (1);
}

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

void	put_pixel(int x, int y, int colour, t_data *data)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}

int	draw_crosshair(t_data *data)
{
	int		y;
	int		x;
	
	y = 0;
	while (y < 480)
	{
		x = 0;
		while (x < 800)
		{
			put_pixel(x, y, 0x00000000, data);
			x++;
		}
		y++;
	}
	x = 0;
	y = 0;
	while (y < data->obj_height)
	{
		put_pixel(data->x_pos + (data->obj_width / 2), data->y_pos + y, 0x00FFFFFF, data);
		y++;
	}
	while (x < data->obj_width)
	{
		put_pixel(data->x_pos + x, data->y_pos + (data->obj_width / 2), 0x00FFFFFF, data);
		x++;
	}
/*	mlx_put_image_to_window(data->mlx, data->window, data->img.img_ptr, 0, 0);*/
	return (1);
}

int		keypress(int keycode, t_data *data)
{
	if (keycode == 53)
		exit_window(data);
	if (keycode == 13)
		if (data->y_pos > 0)
			data->y_pos--;
	if (keycode == 1)
		if (data->y_pos < 480)
			data->y_pos++;
	if (keycode == 0)
		if (data->x_pos > 0)
			data->x_pos--;
	if (keycode == 2)
		if (data->x_pos < 800)
			data->x_pos++;
	/*draw_crosshair(data);*/
	return (1);
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
			put_pixel(x, y, 0x00FFFFFF, data);
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

void	draw_player(t_data *data)
{
	put_pixel(data->x_pos, data->y_pos, 0x00FF0000, data);
	put_pixel(data->x_pos, data->y_pos + 1, 0x00FF0000, data);
	put_pixel(data->x_pos + 1, data->y_pos, 0x00FF0000, data);
	put_pixel(data->x_pos + 1, data->y_pos + 1, 0x00FF0000, data);
}

int		draw_2d_map(t_data *data)
{
	int x;
	int y;
	int xo;
	int yo;

	y = 0;
	while (y < 480)
	{
		x = 0;
		while (x < 800)
		{
			put_pixel(x, y, 0x00000000, data);
			x++;
		}
		y++;
	}
	y = 0;
	x = 0;
	while (y < map_y)
	{
		x = 0;
		while (x < map_x)
		{
			xo = x * map_size;
			yo = y * map_size;
			if (map[y * map_x + x] == 1)
				draw_cube(xo + 1, xo + map_size - 1, yo + 1, yo + map_size - 1, 0x00000000, data);
			else
				draw_cube(xo + 1, xo + map_size - 1, yo + 1, yo + map_size - 1, 0x00FFFFFF, data);
			x++;
		}
		y++;
	}
	put_pixel(data->x_pos, data->y_pos, 0x00FF0000, data);
	put_pixel(data->x_pos, data->y_pos + 1, 0x00FF0000, data);
	put_pixel(data->x_pos + 1, data->y_pos, 0x00FF0000, data);
	put_pixel(data->x_pos + 1, data->y_pos + 1, 0x00FF0000, data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img_ptr, 0, 0);
	return (1);
}

int		window_loop(t_data *data)
{
	/*mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->img.img_ptr);
	init_environment(data);
	draw_2d_map(data);
	draw_player(data);
	*/
	draw_2d_map(data);
	/*draw_player(data);*/
	/*mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data->window);*/
	return (1);
}

int		loops(t_data *data)
{
	mlx_hook(data->window, 17, 0L, exit_window, data);
	mlx_hook(data->window, 2, (1L<<0), keypress, data);
	mlx_loop_hook(data->mlx, draw_2d_map, data);
	mlx_loop(data->mlx);
	return (0);
}
int		main(void)
{
	t_data		data;

	init_data(&data);
	start_mlx(&data);
	/*
	init_environment(&data);
	draw_2d_map(&data);
	draw_player(&data);
	*/
	loops(&data);
	/*mlx_key_hook(data.window, key_press_hook, &data);*/

	
	return (0);
}
