/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 14:57:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/23 16:52:47 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	*start_mlx(t_data *data)
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

int	loops(t_data *data)
{
	mlx_hook(data->window, 17, 0L, exit_window, data);
	mlx_hook(data->window, 2, (1L << 0), key_press, data);
	mlx_loop_hook(data->mlx, &window_loop, data);
	mlx_hook(data->window, 3, (1L << 1), key_release, data);
	mlx_loop(data->mlx);
	return (1);
}

static int	validate_input(int argc, char **argv, t_file *file, \
	t_status *status)
{
	size_t	len;

	file->BMP = 0;
	if (argc > 1 && argc < 4)
	{
		len = ft_strlen(argv[1]);
		if (!ft_strcmp(argv[1] + (len - 4), ".cub"))
			file->path = argv[1];
		else
			return (set_status(status, EXTENSION_ERROR));
		if (argc == 3)
		{
			if (!ft_strcmp(argv[2], "--save"))
				file->BMP = 1;
			else
				return (set_status(status, ARGSAVE_ERROR));
		}
	}
	else
		return (set_status(status, ARGNO_ERROR));
	*status = SUCCESS;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_input(argc, argv, &data.file, &data.status))
		return (exit_window(&data));
	init_data(&data);
	if (!parsing(&data))
		return (exit_window(&data));
	loops(&data);
	exit_window(&data);
	return (0);
}
