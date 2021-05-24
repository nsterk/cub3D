/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 16:53:07 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/24 13:35:03 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_status
{
	SUCCESS = 0,
	EXTENSION_ERROR,
	ARGSAVE_ERROR,
	ARGNO_ERROR,
	FILE_ERROR,
	READ_ERROR,
	CONFIG_ERROR,
	MAP_ERROR,
	IMG_ERROR,
	MALLOC_ERROR,
	BMP_ERROR,
}				t_status;

typedef struct s_d2vec
{
	double	x;
	double	y;
}				t_d2vec;

typedef struct s_i2vec
{
	int	x;
	int	y;
}				t_i2vec;

typedef struct s_rgb
{
	unsigned char	B;
	unsigned char	G;
	unsigned char	R;
	unsigned char	T;
}				t_rgb;

typedef union u_colour
{
	unsigned int	colour;
	t_rgb			parts;
}				t_colour;

typedef struct s_img
{
	char	*path;
	void	*ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_tex
{
	t_img	img;
	int		x;
	int		y;
	double	wall_x;
	double	step;
	double	pos;
}				t_tex;

typedef struct s_sprite
{
	int			amount;
	t_img		img;
	t_d2vec		*pos;
	double		*distance;
	int			stripe;
	t_d2vec		cam;
	double		inv;
	t_d2vec		transform;
	int			screen_x;
	int			height;
	int			width;
	t_i2vec		start;
	t_i2vec		end;
	t_i2vec		tex;
}				t_sprite;

typedef struct s_map
{
	char		**grid;
	char		**check;
	int			*x;
	int			y;
	char		spawn_char;
}				t_map;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_file
{
	const char	*path;
	char		*line;
	int			ret;
	int			BMP;
}				t_file;

/*
**	RAYCASTING STRUCT
**	camera_x:	x-coordinate in camera space.
**	side_dist:	distance to next x- or y-side.
**	delta_dist:	distance from one x- or y-side to next.
**	perp_dist:	perpendicular distance to wall.
**	step:		what x- and y-direction to step in (+1 or -1).
**	side:		if horizontal (y/NS) wall or vertical (x/EW) wall is hit.
*/

typedef struct s_ray
{
	t_d2vec		plane;
	double		camera_x;
	t_i2vec		map;
	t_d2vec		dir;
	t_d2vec		side_dist;
	t_d2vec		delta_dist;
	double		perp_dist;
	t_i2vec		step;
	int			side;
	int			line_height;
	int			line_start;
	int			line_end;
	double		*z_buffer;
}				t_ray;

typedef struct s_data
{
	t_status	status;
	void		*mlx;
	void		*window;
	int			mlx_status;
	t_img		img;
	t_file		file;
	t_ray		ray;
	t_map		map;
	t_tex		tex[4];
	t_sprite	spr;
	t_keys		keys;
	t_i2vec		res;
	t_d2vec		pos;
	t_d2vec		dir;
	t_d2vec		plane;
	double		move_speed;
	double		rot_speed;
	int			ceiling;
	int			floor;
}			t_data;

#endif