/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 11:58:10 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/08 17:19:55 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <get_next_line.h>
# include <libft.h>

/*
**	DEFINES
*/
# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124
# define ESC	53

# define MLX_SYNC_IMAGE_WRITABLE		1
# define MLX_SYNC_WIN_FLUSH_CMD			2
# define MLX_SYNC_WIN_CMD_COMPLETED		3

# define WHITE	0x00FFFFFF
# define BLACK	0x00000000
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define YELLOW	0x00FFFF00
# define LIGHTGRAY	0x009E9F8C
# define DARKGRAY	0x007e7f70

# define PI		3.1415926

/*
**	Struct for vector of type double
*/

typedef struct s_d2vec
{
	double	x;
	double	y;
}				t_d2vec;

/*
**	Struct for vector of type integer
*/

typedef struct s_i2vec
{
	int	x;
	int	y;
}				t_i2vec;

typedef struct s_colour
{
	int	R;
	int	G;
	int	B;
}				t_colour;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_pp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_file
{
	const char	*str;
	char		*line;
	char		**map;
	int			*map_x;
	int			map_y;
	t_i2vec		res;
	char		*tex_north;
	char		*tex_south;
	char		*tex_west;
	char		*tex_east;
	char		*tex_sprite;
	t_colour	floor;
	t_colour	ceiling;
}				t_file;

/*
**	RAYCASTING STRUCT
**	camera_x:	x-coordinate in camera space.
**	side_dist:	distance to next x- or y-side.
**	delta_dist:	distance from one x- or y-side to next.
**	perp_dist:	perpendicular distance to wall.
**	step:		what x- and -y direction to step in (+1 or -1).
**	side:		if horizontal (y/NS) wall or vertical (x/EW) wall is hit.
**	line_height: the height of the line corresponding to the ray.
**	line_start:	the y-coordinate to start drawing the line at.
**	line_end:	the y-coordinate to stop drawing the line at.
*/

typedef struct s_ray
{
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
}				t_ray;

/*
**	Time stores the time of the current frame, old_time stores
**	the time of the previous frame: difference between them determines
**	the speed player moves at (in order to keep speed constant no matter how
**	long the calculation takes).
**	ceiling:	ceiling colour.
**	floor:		floor colour.
*/

typedef struct s_data
{
	void		*mlx;
	void		*window;
	double		time;
	double		old_time;
	t_i2vec		res;
	t_d2vec		pos;
	t_d2vec		dir;
	t_d2vec		plane;
	double		move_speed;
	double		rot_speed;
	t_img		img;
	char		**map;
	int			*map_x;
	int			map_y;
	int			ceiling;
	int			floor;
	t_file		file;
}			t_data;

void		init_data(t_data *data);
void		complete_data(t_data *data);

/*
**	Parsing functions.
*/
typedef int	(*t_id)(t_file *file, char *id);
int			parse_start(t_file *file);
int			parse_res(t_file *file, char *line);
int			colour(t_file *file, char *line);
int			parse_colour(t_colour *colour, char *line);
int			parse_map(int fd, t_file *file, int ret);
char		**copy_map(t_list *list, int size);
int			*get_width(t_file *file);
int			create_trgb(int t, int r, int g, int b);

/*
**	Moving functions.
*/

void		move_up(t_data *data);
void		move_down(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);

/*
**	Raycasting functions.
*/

void		raycaster(t_data *data, int x);
void		calc_step_distance(t_data *data, t_ray *ray);
void		differential_analysis(t_data *data, t_ray *ray);
void		calc_line(t_data *data, t_ray *ray);
void		rotate_left(t_data *data);
void		rotate_right(t_data *data);

/*
**	Drawing functions.
*/
void		put_pixel(int x, int y, int colour, t_img *img);
void		put_line(int x, int y0, int y1, int colour, t_img *img);
void		init_environment(t_data *data);

#endif