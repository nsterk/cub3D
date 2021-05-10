/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 11:58:10 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/10 20:44:06 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <get_next_line.h>
# include <libft.h>
# include <stdio.h>

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

/*
**	Structs for vectors of type double & integer
*/

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

typedef struct s_img
{
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
	char	*path;
	t_img	img;
	int		x;
	int		y;
	double	wall_x;
	double	step;
	double	pos;
}				t_tex;

typedef struct s_sprite
{
	char		*path;
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
	int			nr_sprites;
	char		spawn_char;
	t_d2vec		spawn_pos;
	t_d2vec		spawn_dir;
	t_d2vec		plane;
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
	int			fd;
	char		spawn_char;
	int			BMP;
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
	double		time;
	double		old_time;
	double		*z_buffer;
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

void		init_data(t_data *data);
void		pos_sprites(char **map, t_d2vec *pos, int *xmax, int ymax);
int			alloc_sprite(t_sprite *sprites);
int			complete_data(t_data *data);
void		complete_tex(t_data *data);
int			complete_sprites(t_data *data);

char		first_char(char *str);

/*
**	Window management.
*/
int			exit_window(t_data *data);
int			window_loop(t_data *data);
int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);

/*
**	Parsing functions.
*/
typedef int	(*t_id)(t_data *data, char *id);
int			parse_start(t_data *data);
int			parse_res(t_data *data, char *line);
int			parse_tex(t_data *data, char *line);
int			parse_sprite(t_data *data, char *line);
int			colour(t_data *data, char *line);
int			parse_colour(int *colour, char *line);
int			parse_map(t_data *data);
char		**copy_map(t_list *list, int size);
int			get_map_info(t_map *map);
int			validate_map(t_map *map, char **grid);
int			floodfill(int y, int x, t_map *map);
int			create_trgb(int t, int r, int g, int b);

/*
**	Moving functions.
*/

void		move_hooks(t_data *data);
void		move_up(t_data *data);
void		move_down(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);

/*
**	Image to window functions.
*/

void		raycaster(t_data *data, int x);
void		calc_step_distance(t_d2vec pos, t_ray *ray);
void		differential_analysis(t_data *data);
void		calc_line(t_d2vec pos, t_i2vec res, t_ray *ray);
void		rotate_left(t_data *data);
void		rotate_right(t_data *data);
void		calc_texture(t_data *data, int i);
void		put_texture(t_data *data, int x, int i);

int			draw_sprites(t_data *data);
void		sort_sprites(t_sprite *spr);
void		calculate_sprite(t_data *data, int i);
void		put_sprite(t_data *data);
void		put_pixel_sprite(t_data *data, int y);

/*
**	Drawing functions.
*/
void		put_pixel(int x, int y, int colour, t_img *img);
void		put_line(int x, t_ray *ray, int colour, t_img *img);

int			create_bmp(t_i2vec res, t_img *img);
#endif