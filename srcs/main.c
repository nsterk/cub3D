/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 14:57:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/07 13:38:51 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
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
	data->window = mlx_new_window(data->mlx, data->res.x, data->res.y, "cub3D");
	if (!data->window)
		return (NULL);
	data->img.ptr = mlx_new_image(data->mlx, data->res.x, data->res.y);
	if (!data->img.ptr)
		return (NULL);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp,
			&data->img.len, &data->img.endian);
	if (!data->img.addr)
		return (NULL);
	return ("1");
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		exit_window(data);
	if (keycode == D)
		data->keys.d = 1;
	if (keycode == A)
		data->keys.a = 1;
	if (keycode == W)
		data->keys.w = 1;
	if (keycode == S)
		data->keys.s = 1;
	if (keycode == LEFT)
		data->keys.left = 1;
	if (keycode == RIGHT)
		data->keys.right = 1;
	return (1);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == D)
		data->keys.d = 0;
	if (keycode == A)
		data->keys.a = 0;
	if (keycode == W)
		data->keys.w = 0;
	if (keycode == S)
		data->keys.s = 0;
	if (keycode == LEFT)
		data->keys.left = 0;
	if (keycode == RIGHT)
		data->keys.right = 0;
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
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->img.ptr);
	init_environment(data);
	move_hooks(data);
	while (x < data->res.x)
	{
		raycaster(data, x);
		x++;
	}
	draw_sprites(data);
	if (data->file.BMP)
	{
		data->file.BMP = 0;
		create_bmp(data->res, &data->img);
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data->window);
	return (1);
}

int	loops(t_data *data)
{
	mlx_hook(data->window, 17, 0L, exit_window, data);
	mlx_hook(data->window, 2, (1L << 0), key_press, data);
	mlx_loop_hook(data->mlx, &window_loop, data);
	mlx_hook(data->window, 3, (1L << 1), key_release, data);
	mlx_loop(data->mlx);
	return (1);
}

int	validate_input(int argc, char **argv, t_file *file)
{
	if (argc >= 2)
	{
		file->path = argv[1];
		file->BMP = 1;
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
