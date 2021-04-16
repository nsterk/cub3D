/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 14:57:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/16 20:50:11 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

int	exit_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(1);
	return (1);
}

static void	*start_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (NULL);
	data->window = mlx_new_window(data->mlx, data->res.x, data->res.y, "mert");
	if (!data->window)
		return (NULL);
	data->img.img_ptr = mlx_new_image(data->mlx, data->res.x, data->res.y);
	if (!data->img.img_ptr)
		return (NULL);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_pp,
			&data->img.len, &data->img.endian);
	if (!data->img.addr)
		return (NULL);
	return ("1");
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit_window(data);
	if (keycode == D)
	{
		move_right(data);
	}
	if (keycode == A)
	{
		move_left(data);
	}
	if (keycode == W)
	{
		move_up(data);
	}
	if (keycode == S)
	{
		move_down(data);
	}
	if (keycode == LEFT)
		rotate_left(data);
	if (keycode == RIGHT)
		rotate_right(data);
	return (1);
}

void	init_environment(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->res.y)
	{
		x = 0;
		while (x < data->res.x)
		{
			if (y < (data->res.y / 2))
				put_pixel(x, y, data->ceiling, &data->img);
			else
				put_pixel(x, y, data->floor, &data->img);
			x++;
		}
		y++;
	}
}

int	window_loop(t_data *data)
{
	int	x;

	x = 0;
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->img.img_ptr);
	init_environment(data);
	while (x < data->res.x)
	{
		raycaster(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img.img_ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data->window);
	return (1);
}

int	loops(t_data *data)
{
	mlx_hook(data->window, 17, 0L, exit_window, data);
	mlx_hook(data->window, 2, (1L << 0), keypress, data);
	mlx_loop_hook(data->mlx, &window_loop, data);
	mlx_loop(data->mlx);
	return (1);
}

int	validate_input(int argc, char **argv, t_file *file)
{
	if (argc >= 2)
	{
		file->path = argv[1];
	}
	else
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_input(argc, argv, &data.file))
		return (0);
	init_data(&data);
	parse_start(&data);
	start_mlx(&data);
	complete_data(&data);
	init_environment(&data);
	loops(&data);
	return (0);
}
