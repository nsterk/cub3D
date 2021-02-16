/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 11:58:10 by nsterk        #+#    #+#                 */
/*   Updated: 2021/02/16 17:53:54 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <get_next_line.h>

typedef struct	s_mlx_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx_data;

typedef struct s_data
{
	void		*do_mlx;
	void		*window;
	int			y_res;
	int			x_res;
	t_mlx_data	mlx;
}				t_data;

/*
**	Global variables
*/
t_data		data;
int			map_x = 6;
int			map_y = 6;
int			map_size = 36;
int			map[] =
{
	1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1,
}

#endif