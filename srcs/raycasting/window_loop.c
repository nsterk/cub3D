/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_loop.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 15:22:51 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/13 20:01:41 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	init_environment(t_data *data)
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
		if (!create_bmp(data->res, &data->img))
			set_status(&data->status, BMP_ERROR);
		exit_window(data);
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data->window);
	return (1);
}
