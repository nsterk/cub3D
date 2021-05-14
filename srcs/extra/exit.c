/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 19:09:30 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/14 00:06:18 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <fcntl.h>

static void	write_error_msg(t_status status)
{
	static const char	*msg[11] =
	{
		"Successful game exit",
		"Incorrect file extension, expect .cub",
		"Incorrect 2nd argument provided. Specify save using --save",
		"Expect minimum 1 and maximum 2 aguments",
		"Unable to open configuration file",
		"Error reading configuration file",
		"Invalid configuration file",
		"Invalid map",
		"Unable to create window",
		"Memory allocation failure",
		"Unable to save screenshot",
	};

	printf("Error\n%s\n", msg[status]);
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
