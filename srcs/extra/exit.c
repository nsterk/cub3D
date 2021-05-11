/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 19:09:30 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/11 19:49:13 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <fcntl.h>

static void	write_error_msg(t_status status)
{
	static const char	*msg[4] =
	{
		"Successful game exit",
		"Incorrect file extension, expect .cub",
		"Incorrect 2nd argument provided. Specify save using --save",
		"Expect minimum 1 and maximum 2 aguments",
		"Unable to open file",
	};

	printf("Error\n%s\n", msg[status]);
}

static void	close_free(t_data *data)
{
	if (data->file.fd != -1)
		close(data->file.fd);
}

int	exit_window(t_data *data)
{
	if (data->status != SUCCESS)
		write_error_msg(data->status);
	if (data->mlx)
		mlx_destroy_window(data->mlx, data->window);
	close_free(data);
	exit(1);
	return (0);
}
