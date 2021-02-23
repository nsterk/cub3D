/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 11:58:10 by nsterk        #+#    #+#                 */
/*   Updated: 2021/02/22 20:50:43 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <get_next_line.h>

/*
**	Definitions
*/

# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124
# define ESC	53

# define SPEED	3

# define MLX_SYNC_IMAGE_WRITABLE		1
# define MLX_SYNC_WIN_FLUSH_CMD			2
# define MLX_SYNC_WIN_CMD_COMPLETED		3

typedef struct	s_img {
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;


typedef struct s_data
{
	void		*mlx;
	void		*window;
	int			y_res;
	int			x_res;
	int			obj_height;
	int			obj_width;
	int			y_pos;
	int			x_pos;
	int			speed;
	t_img		img;
}				t_data;

/*
**	Global variables
*/
/*
t_data		data;*/
int			map_x = 8;
int			map_y = 8;
int			map_size = 64;
int			map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

#endif